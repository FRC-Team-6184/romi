// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc/GenericHID.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/Commands.h>
#include <frc2/command/button/Button.h>

#include "commands/TeleopArcadeDrive.h"
#include "commands/TeleopTankDrive.h"

RobotContainer::RobotContainer() { ConfigureButtonBindings(); }

void RobotContainer::ConfigureButtonBindings()
{
  drivetrain.SetName("Cow Town");
  drivetrain.SetDefaultCommand(TeleopArcadeDrive(
      &drivetrain,
      [this]
      {
        return (-controller.GetLeftY());
      },
      [this]
      {
        return (-controller.GetLeftX());
      }));
  // drivetrain.SetDefaultCommand(TeleopArcadeDrive(
  //     &drivetrain,
  //     [this]
  //     {
  //       return ((-controller.GetRightY() / 2) - (controller.GetLeftY() / 2)) *
  //              (speedMultiplier + controller.GetL2Axis() * 0.5);
  //     },
  //     [this]
  //     {
  //       return ((-controller.GetRightY() / 2) + (controller.GetLeftY() / 2)) *
  //              (speedMultiplier + controller.GetL2Axis() * 0.5);
  //     }));
  // drivetrain.SetDefaultCommand(TeleopTankDrive(
  //     &drivetrain,
  //     [this]
  //     {
  //       return (-controller.GetLeftY());
  //     },
  //     [this]
  //     {
  //       return (-controller.GetRightY());
  //     }));

  onSquare.OnTrue(frc2::cmd::Print("Square Button Pressed"))
      .OnFalse(frc2::cmd::Print("Square Button Released"));
  onTriangle.OnTrue(frc2::cmd::Print("Triangle Button Pressed"))
      .OnFalse(frc2::cmd::Print("Triangle Button Released"));
  onCircle.OnTrue(frc2::cmd::Print("Circle Button Pressed"))
      .OnFalse(frc2::cmd::Print("Circle Button Released"));
  onCross.OnTrue(frc2::cmd::Print("Cross Button Pressed"))
      .OnFalse(frc2::cmd::Print("Cross Button Released"));

  // Setup SmartDashboard options.
  sendableChooser.SetDefaultOption("Auto Routine Distance", &autoDistance);
  sendableChooser.AddOption("Auto Routine Time", &autoTime);
  frc::SmartDashboard::PutData("Auto Selector", &sendableChooser);
  // Choose drive mode
  // gameModeChooser.SetDefaultOption("Tank Drive");
}

frc2::Command *RobotContainer::GetAutonomousCommand()
{
  return sendableChooser.GetSelected();
}
