#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "modules.h"


void Gui::DrawSliders(){
  DrawRectangle(0,0, 345, 275, {232, 232, 232, 255});
  DrawFPS(0,0);
  DrawText("Backspace = camera control", 85, 0, 18, GRAY);

  GuiSliderBar({115,30, 200, 40}, "Speed", TextFormat("%.2f", Update::speed), &Update::speed, 0, 10.0f); 
  GuiSliderBar({115,70, 200, 40}, "Seperation Distance", TextFormat("%.2f", Update::seperation_dist), &Update::seperation_dist, 0, 10.0f); 
  GuiSliderBar({115,110, 200, 40}, "Seperation Scale", TextFormat("%.2f", Update::seperation_scaling), &Update::seperation_scaling, 0, 10.0f); 
  GuiSliderBar({115,150, 200, 40}, "Flock Distance", TextFormat("%.2f", Update::flock_dist), &Update::flock_dist,  0, 10.0f); 
  GuiSliderBar({115,190, 200, 40}, "Alignment Scaling", TextFormat("%.2f", Update::alignment_scaling), &Update::alignment_scaling, 0, 10.0f); 
  GuiSliderBar({115,230, 200, 40}, "Cohesion Scaling", TextFormat("%.2f", Update::cohesion_scaling), &Update::cohesion_scaling, 0, 10.0f); 
}
