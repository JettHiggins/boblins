#include "raylib.h"
#include "screens.h"
#include "./game/modules.h"

GameScreen currentScreen = GAME;
Music music {0};

static const int screenWidth = 1200;
static const int screenHeight = 675;

static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = UNKNOWN;

// Declare these functions so main knows they exist
static void ChangeToScreen(GameScreen screen);     // Change to screen, no transition effect

static void TransitionToScreen(GameScreen screen); // Request transition to next screen
static void UpdateTransition(void);         // Update transition effect
static void DrawTransition(void);           // Draw transition effect (full-screen rectangle)

static void UpdateDrawFrame(void);          // Update and draw one frame


int main(void)
{
  InitWindow(screenWidth, screenHeight, "Template");
  InitAudioDevice();

  currentScreen = GAME;
  Renderer::initRenderer();
  Update::initGame({{0,0,0}, Renderer::camera.position});

  SetTargetFPS(0);

  while (!WindowShouldClose())
  {
    UpdateDrawFrame();
  }

  //Unload current screen before closing
  switch (currentScreen)
  {
    case LOGO: UnloadLogoScreen(); break;
    default: break;
  }

  CloseAudioDevice();
  CloseWindow();

  return 0;
}

// This function takes a screen as input and will unload current and load the next one
static void ChangeToScreen(GameScreen screen)
{
  // Unload current screen
  switch (currentScreen)
  {
    case LOGO: UnloadLogoScreen(); break;
    case GAME: Renderer::unloadRenderer(); break;
    default: break;
  }

  // Init next screen
  switch (screen)
  {
    case LOGO: InitLogoScreen(); break;
    default: break;
  }

  currentScreen = screen;
}

//Set transition variables - actual transition is handled by UpdateTransition
static void TransitionToScreen(GameScreen screen)
{
  onTransition = true;
  transFadeOut = false;
  transFromScreen = currentScreen;
  transToScreen = screen;
  transAlpha = 0.0f;
}

//Fades in then reverses to fade out, this works becuase if we are in the transition state we draw a rect over the whole window with size screen
static void UpdateTransition(void)
{
  if (!transFadeOut)
  {
    transAlpha += 0.05f;

    // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
    // For that reason we compare against 1.01f, to avoid last frame loading stop
    if (transAlpha > 1.01f)
    {
      transAlpha = 1.0f;

      // Unload current screen
      switch (transFromScreen)
      {
        case LOGO: UnloadLogoScreen(); break;
        default: break;
      }

      // Load next screen
      switch (transToScreen)
      {
        case LOGO: InitLogoScreen(); break;
        default: break;
      }

      currentScreen = transToScreen;

      switch(currentScreen)
      {
        case LOGO: UpdateLogoScreen(); break;
        default: break;
      }

      // Activate fade out effect to next loaded screen
      transFadeOut = true;
    }
  }
  else  // Transition fade out logic
  {
    transAlpha -= 0.02f;

    if (transAlpha < -0.01f)
    {
      transAlpha = 0.0f;
      transFadeOut = false;
      onTransition = false;
      transFromScreen = -1;
      transToScreen = UNKNOWN;
    }
  }
}

//Rect that fades in out to mask transition
static void DrawTransition(void)
{
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

//Update the screen depending on current screen/transition
static void UpdateDrawFrame(void)
{
  // Update
  //----------------------------------------------------------------------------------

  if (IsMusicValid(music)) UpdateMusicStream(music);
  if (!onTransition)
  {
    switch(currentScreen)
    {
      case GAME:
        Update::updateGame();
        break;
      case LOGO:
        {
          UpdateLogoScreen();

          if (FinishLogoScreen()) TransitionToScreen(LOGO);

        } break;
      default: break;
    }
  }
  else UpdateTransition();    // Update transition (fade-in, fade-out)
                              //----------------------------------------------------------------------------------

                              // Draw
                              //----------------------------------------------------------------------------------
  BeginDrawing();

  ClearBackground(RAYWHITE);

  switch(currentScreen)
  {
    case LOGO: DrawLogoScreen(); break;
    case GAME: Renderer::drawGame(Update::things); break;
    default: break;
  }

  // Draw full screen rectangle in front of everything
  if (onTransition) DrawTransition();


  EndDrawing();
  //----------------------------------------------------------------------------------
}
