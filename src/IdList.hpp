#ifndef _IDLIST_HPP_INCLUDED
#define _IDLIST_HPP_INCLUDED

/// \enum EMenu
// TODO renommer en NGuiIds
namespace NGuiIds {

    // Normalement je pourrai separer les differents enums
//enum class EOptionsIds {
//BackToMenu = 101,
//BackToGame,
//SaveConfig,
//ResetConfig,
//
//};


enum EId {


// Main menu
Play = 0,
Options = 1,
ViewScores =2,
Credits = 3,
QuitGame  = 4,

// Credits
CreditsWindow = 5,

// allow choice between models
SetModelToYF19 = 6,
SetModelToYF21 = 7,


// Engine id
ErrorTab = 8,



// Options Menu
BackToMenu = 9,
BackToGame = 10,
SaveConfig = 11,
ResetConfig = 12,
ContinueGame = 13,
SaveScore = 14,

// Menu pdt jeu solo

 // aussi dispo


// Graphic tab
//GraphicTabFirstId
VideoModeList = 15,
FullscreenBox = 16,
MotionBlurShader = 17,
BloomShader = 18,
VSync = 19,
Resolution = 20,
VideoDriver = 21,
Antialiasing = 22,


// Sound tab
//SoundTabFirstId,
VolumeControl = 23,
AudioDriver = 24,
//SoundTabLastId,
// User tab
// Gameplay tab
SkipDialog = 25,
Language = 26,


//
DialogBox = 27,
DialogImage = 28,
DialogText = 29,
DialogAnswers = 30,


//
Console = 31,

Count
};

}

#endif
