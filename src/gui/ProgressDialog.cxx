//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2020 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#include "bspf.hxx"
#include "OSystem.hxx"
#include "FrameBuffer.hxx"
#include "Widget.hxx"
#include "Dialog.hxx"
#include "Font.hxx"
#include "DialogContainer.hxx"
#include "ProgressDialog.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
ProgressDialog::ProgressDialog(GuiObject* boss, const GUI::Font& font,
                               const string& message)
  : Dialog(boss->instance(), boss->parent())
{
  const int fontWidth  = font.getMaxCharWidth(),
            fontHeight = font.getFontHeight(),
            lineHeight = font.getLineHeight(),
            VBORDER = fontHeight / 2,
            HBORDER = fontWidth * 1.25,
            VGAP = fontHeight / 4;
  int xpos, ypos, lwidth;

  // Calculate real dimensions
  lwidth = font.getStringWidth(message);
  _w = HBORDER * 2 + lwidth;
  _h = VBORDER * 2 + lineHeight * 2 + VGAP * 2;

  xpos = HBORDER; ypos = VBORDER;
  myMessage = new StaticTextWidget(this, font, xpos, ypos, lwidth, fontHeight,
                                   message, TextAlign::Center);
  myMessage->setTextColor(kTextColorEm);

  xpos = HBORDER; ypos += lineHeight + VGAP * 2;
  mySlider = new SliderWidget(this, font, xpos, ypos, lwidth, lineHeight, "", 0, 0);
  mySlider->setMinValue(1);
  mySlider->setMaxValue(100);

  open();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ProgressDialog::setMessage(const string& message)
{
  myMessage->setLabel(message);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ProgressDialog::setRange(int start, int finish, int step)
{
  myStart = start;
  myFinish = finish;
  myStep = int((step / 100.0) * (myFinish - myStart + 1));

  mySlider->setMinValue(myStart);
  mySlider->setMaxValue(myFinish);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void ProgressDialog::setProgress(int progress)
{
  // Only increase the progress bar if we have arrived at a new step
  if(progress - mySlider->getValue() > myStep)
  {
    mySlider->setValue(progress);

    // Since this dialog is usually called in a tight loop that doesn't
    // yield, we need to manually tell the framebuffer that a redraw is
    // necessary
    // This isn't really an ideal solution, since all redrawing and
    // event handling is suspended until the dialog is closed
    instance().frameBuffer().update();
  }
}
