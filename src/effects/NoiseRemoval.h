/**********************************************************************

  Audacity: A Digital Audio Editor

  NoiseRemoval.h

  Dominic Mazzoni
  Vaughan Johnson (Preview)

**********************************************************************/

#ifndef __AUDACITY_EFFECT_NOISE_REMOVAL__
#define __AUDACITY_EFFECT_NOISE_REMOVAL__

#include "../Audacity.h"

#include "../Experimental.h"

#if !defined(EXPERIMENTAL_NOISE_REDUCTION)

#include "Effect.h"

#include <wx/dialog.h>
#include <wx/slider.h>

class wxButton;
class wxSizer;
class wxString;

class Envelope;
class WaveTrack;

#include "../RealFFTf.h"

class EffectNoiseRemoval final : public Effect
{
public:
   EffectNoiseRemoval();
   virtual ~EffectNoiseRemoval();

   // IdentInterface implementation

   virtual wxString GetSymbol();
   virtual wxString GetDescription();

   // EffectIdentInterface implementation

   virtual EffectType GetType();
   virtual bool SupportsAutomation();

   // Effect implementation

   virtual bool PromptUser();
   virtual bool Init();
   virtual bool CheckWhetherSkipEffect();
   virtual bool Process();

private:

   bool      mDoProfile;
   bool      mHasProfile;
   int       mLevel;

   // Parameters chosen before the first phase
   double    mSampleRate;
   int       mWindowSize;
   int       mSpectrumSize;
   float     mMinSignalTime;    // in secs

   // The frequency-indexed noise threshold derived during the first
   // phase of analysis
   float    *mNoiseThreshold;  // length is mSpectrumSize

   // Parameters that affect the noise removal, regardless of how the
   // noise profile was extracted
   double     mSensitivity;
   double     mFreqSmoothingHz;
   double     mNoiseGain;              // in dB, should be negative
   double     mAttackDecayTime;        // in secs
   bool       mbLeaveNoise;

   bool ProcessOne(int count, WaveTrack * track,
                   sampleCount start, sampleCount len);

   void Initialize();
   void StartNewTrack();
   void ProcessSamples(sampleCount len, float *buffer);
   void FillFirstHistoryWindow();
   void ApplyFreqSmoothing(float *spec);
   void GetProfile();
   void RemoveNoise();
   void RotateHistoryWindows();
   void FinishTrack();
   void Cleanup();

   // Variables that only exist during processing
   WaveTrack            *mOutputTrack;
   sampleCount       mInSampleCount;
   sampleCount       mOutSampleCount;
   int                   mInputPos;

   HFFT     hFFT;
   float    *mFFTBuffer;         // mWindowSize
   float    *mWindow;            // mWindowSize

   int       mFreqSmoothingBins;
   int       mAttackDecayBlocks;
   float     mOneBlockAttackDecay;
   float     mNoiseAttenFactor;
   float     mSensitivityFactor;
   int       mMinSignalBlocks;
   int       mHistoryLen;
   float    *mInWaveBuffer;     // mWindowSize
   float    *mOutOverlapBuffer; // mWindowSize
   float   **mSpectrums;        // mHistoryLen x mSpectrumSize
   float   **mGains;            // mHistoryLen x mSpectrumSize
   float   **mRealFFTs;         // mHistoryLen x mWindowSize
   float   **mImagFFTs;         // mHistoryLen x mWindowSize

   friend class NoiseRemovalDialog;
};

// WDR: class declarations

//----------------------------------------------------------------------------
// NoiseRemovalDialog
//----------------------------------------------------------------------------

// Declare window functions

class NoiseRemovalDialog final : public EffectDialog
{
public:
   // constructors and destructors
   NoiseRemovalDialog(EffectNoiseRemoval * effect,
                      wxWindow *parent);

   wxSizer *MakeNoiseRemovalDialog(bool call_fit = true,
                                   bool set_sizer = true);

   void PopulateOrExchange(ShuttleGui & S);
   bool TransferDataToWindow();
   bool TransferDataFromWindow();

private:
   // handlers
   void OnGetProfile( wxCommandEvent &event );
   void OnKeepNoise( wxCommandEvent &event );
   void OnPreview(wxCommandEvent &event);
   void OnRemoveNoise( wxCommandEvent &event );
   void OnCancel( wxCommandEvent &event );

   void OnSensitivityText(wxCommandEvent & event);
   void OnGainText(wxCommandEvent & event);
   void OnFreqText(wxCommandEvent & event);
   void OnTimeText(wxCommandEvent & event);
   void OnSensitivitySlider(wxCommandEvent & event);
   void OnGainSlider(wxCommandEvent & event);
   void OnFreqSlider(wxCommandEvent & event);
   void OnTimeSlider(wxCommandEvent & event);

 public:

   EffectNoiseRemoval * m_pEffect;

   wxButton * m_pButton_GetProfile;
   wxButton * m_pButton_Preview;
   wxButton * m_pButton_RemoveNoise;

   wxRadioButton *mKeepSignal;
   wxRadioButton *mKeepNoise;

   wxSlider   *mSensitivityS;
   wxSlider   *mGainS;
   wxSlider   *mFreqS;
   wxSlider   *mTimeS;

   wxTextCtrl *mSensitivityT;
   wxTextCtrl *mGainT;
   wxTextCtrl *mFreqT;
   wxTextCtrl *mTimeT;

   double      mSensitivity;
   double      mGain;
   double      mFreq;
   double      mTime;

   bool        mbLeaveNoise;

private:
   DECLARE_EVENT_TABLE()

};

#endif

#endif
