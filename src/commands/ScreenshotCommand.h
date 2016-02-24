/**********************************************************************

   Audacity - A Digital Audio Editor
   Copyright 1999-2009 Audacity Team
   License: GPL v2 - see LICENSE.txt

   Dominic Mazzoni
   Dan Horgan

**********************************************************************/

#ifndef __SCREENSHOTCOMMAND__
#define __SCREENSHOTCOMMAND__

#include "Command.h"
#include "CommandType.h"

#include <wx/colour.h>
class wxWindow;
class wxTopLevelWindow;
class wxCommandEvent;
class wxRect;
class ToolManager;
class CommandOutputTarget;

class ScreenshotCommandType final : public CommandType
{
public:
   virtual wxString BuildName();
   virtual void BuildSignature(CommandSignature &signature);
   virtual Command *Create(CommandOutputTarget *target);
};

class ScreenshotCommand final : public CommandImplementation
{
private:
   // May need to ignore the screenshot dialog
   wxWindow *mIgnore;

   bool mBackground;
   wxColour mBackColor;

   wxString MakeFileName(const wxString &path, const wxString &basename);

   wxRect GetBackgroundRect();
   void Capture(const wxString &basename,
         wxWindow *window,
         int x, int y, int width, int height,
         bool bg = false);
   void CaptureToolbar(ToolManager *man, int type, const wxString &name);
   void CaptureDock(wxWindow *win, const wxString &fileName);

public:
   wxTopLevelWindow *GetFrontWindow(AudacityProject *project);
   ScreenshotCommand(CommandType &type,
                     CommandOutputTarget *output,
                     wxWindow *ignore = NULL)
      : CommandImplementation(type, output),
        mIgnore(ignore),
        mBackground(false)
   { }
   bool Apply(CommandExecutionContext context);
};

#endif /* End of include guard: __SCREENSHOTCOMMAND__ */
