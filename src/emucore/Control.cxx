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
// Copyright (c) 1995-2019 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#include <cassert>

#include "System.hxx"
#include "Control.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Controller::Controller(Jack jack, const Event& event, const System& system,
                       Type type)
  : myJack(jack),
    myEvent(event),
    mySystem(system),
    myType(type),
    myOnAnalogPinUpdateCallback(nullptr)
{
  resetDigitalPins();
  resetAnalogPins();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
uInt8 Controller::read()
{
  uInt8 ioport = 0b0000;
  if(read(DigitalPin::One))   ioport |= 0b0001;
  if(read(DigitalPin::Two))   ioport |= 0b0010;
  if(read(DigitalPin::Three)) ioport |= 0b0100;
  if(read(DigitalPin::Four))  ioport |= 0b1000;
  return ioport;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool Controller::read(DigitalPin pin)
{
  return getPin(pin);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Int32 Controller::read(AnalogPin pin)
{
  return getPin(pin);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool Controller::save(Serializer& out) const
{
  try
  {
    // Output the digital pins
    out.putBool(getPin(DigitalPin::One));
    out.putBool(getPin(DigitalPin::Two));
    out.putBool(getPin(DigitalPin::Three));
    out.putBool(getPin(DigitalPin::Four));
    out.putBool(getPin(DigitalPin::Six));

    // Output the analog pins
    out.putInt(getPin(AnalogPin::Five));
    out.putInt(getPin(AnalogPin::Nine));
  }
  catch(...)
  {
    cerr << "ERROR: Controller::save() exception\n";
    return false;
  }
  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool Controller::load(Serializer& in)
{
  try
  {
    // Input the digital pins
    setPin(DigitalPin::One,   in.getBool());
    setPin(DigitalPin::Two,   in.getBool());
    setPin(DigitalPin::Three, in.getBool());
    setPin(DigitalPin::Four,  in.getBool());
    setPin(DigitalPin::Six,   in.getBool());

    // Input the analog pins
    setPin(AnalogPin::Five, in.getInt());
    setPin(AnalogPin::Nine, in.getInt());
  }
  catch(...)
  {
    cerr << "ERROR: Controller::load() exception\n";
    return false;
  }
  return true;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string Controller::getName(const Type type)
{
  string NAMES[int(Controller::Type::LastType)] =
  {
    "Unknown",
    "AmigaMouse", "AtariMouse", "AtariVox", "BoosterGrip", "CompuMate",
    "Driving", "Sega Genesis", "Joystick", "Keyboard", "KidVid", "MindLink",
    "Paddles", "Paddles_IAxis", "Paddles_IAxDr", "SaveKey", "TrakBall"
  };

  return NAMES[int(type)];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string Controller::getPropName(const Type type)
{
  string PROP_NAMES[int(Controller::Type::LastType)] =
  {
    "AUTO",
    "AMIGAMOUSE", "ATARIMOUSE", "ATARIVOX", "BOOSTERGRIP", "COMPUMATE",
    "DRIVING", "GENESIS", "JOYSTICK", "KEYBOARD", "KIDVID", "MINDLINK",
    "PADDLES", "PADDLES_IAXIS", "PADDLES_IAXDR", "SAVEKEY", "TRAKBALL"
  };

  return PROP_NAMES[int(type)];
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Controller::Type Controller::getType(const string& propName)
{
  for(int i = 0; i < static_cast<int>(Type::LastType); ++i)
  {
    if(BSPF::equalsIgnoreCase(propName, getPropName(Type(i))))
    {
      return Type(i);
    }
  }
  // special case
  if(BSPF::equalsIgnoreCase(propName, "KEYPAD"))
    return Type::Keyboard;

  return Type::Unknown;
}
