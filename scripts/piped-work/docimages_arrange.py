# docimages_arrange.py
# Sends commands to get images for the manual.
# These ones arrange tracks and do alignment.

# Make sure Audacity is running first and that mod-script-pipe is enabled
# before running this script.

# load and run the common core.
exec(open("docimages_core.py").read())


def loadFourColours():
    loadMonoTracks(4)
    do('SelectTrack: Track=0')
    do('SetTrack: Name="Claire" Height=60 Color=Color0')
    do('SetClip: At=1 Start=25')
    do('SelectTrack: Track=1')
    do('SetTrack: Track=1 Name="Ann" Height=60 Color=Color1')
    do('SetClip: At=1 Start=15')
    do('SelectTrack: Track=2')
    do('SetTrack: Track=2 Name="Bob" Height=60 Color=Color2')
    do('SetClip: At=1 Start=20')
    do('SelectTrack: Track=3')
    do('SetTrack: Track=3 Name="David" Height=60 Color=Color3')
    do('SetClip: At=1 Start=10')
    do('Select: TrackCount=100 Mode=Remove')


def loadFourColoursSelected():
    loadFourColours()
    do('ZoomOut')
    do('Select: Start=90 End=135 Track=0 TrackCount=100')


def blockMoves(name):
    # These are the align commands that move tracks 'en block'.
    loadFourColoursSelected()
    capture(name + '001.png', 'All_Tracks_Plus')
    do('Align_StarttoZero')
    capture(name + '002.png', 'All_Tracks_Plus')
    loadFourColoursSelected()
    do('Align_StarttoCursorSelectionStart')
    capture(name + '003.png', 'All_Tracks_Plus')
    loadFourColoursSelected()
    do('Align_StarttoSelectionEnd')
    capture(name + '004.png', 'All_Tracks_Plus')
    loadFourColoursSelected()
    do('Align_EndtoCursorSelectionStart')
    capture(name + '005.png', 'All_Tracks_Plus')
    loadFourColoursSelected()
    do('Align_EndtoSelectionEnd')
    capture(name + '006.png', 'All_Tracks_Plus')


def track_moves(type):
    loadFourColours()
    # Sorting tracks into order
    do('SetTrack: Track=1 Focused=1')
    capture('TrackOrder002.png', 'All_Tracks')


def arrange_imagesA():
    loadFourColours()
    # Moving tracks up and down.
    capture('TrackOrder001.png', 'All_Tracks')
    do('SetTrack: Track=1 Focused=1')
    # ToTop=0 to show the focus...
    capture('TrackOrder002.png', 'All_Tracks ToTop=0')
    do('TrackMoveUp')
    capture('TrackUp.png', 'All_Tracks ToTop=0')
    do('TrackMoveDown')  # undo
    do('TrackMoveDown')
    capture('TrackDown.png', 'All_Tracks ToTop=0')
    do('TrackMoveTop')
    capture('TrackTop.png', 'All_Tracks ToTop=0')
    do('TrackMoveBottom')
    capture('TrackBottom.png', 'All_Tracks ToTop=0')
    # Sorting tracks into order
    do('SortByName')
    capture('TrackOrder003.png', 'All_Tracks')
    do('SortByTime')
    capture('TrackOrder004.png', 'All_Tracks')
    # Aligning tracks
    do('Select: First=0 Last=100 From=0 To=0')
    do('Align_AlignTogether')
    capture('TrackAlign001.png', 'All_Tracks')
    do('Align_AlignEndtoEnd')
    do('FitInWindow')
    capture('TrackAlign002.png', 'All_Tracks')


def arrange_imagesB():
    blockMoves('BlockMoves')
    do('MoveSelectionWithTracks')
    blockMoves('BlockAndCursorMoves')
    do('MoveSelectionWithTracks')


# quickTest()

arrange_imagesA()
# arrange_imagesB()
