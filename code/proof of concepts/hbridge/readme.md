# H-Bridge proof of concept

minimale hard- & software + stappenplan dat aantoont dat 2 motoren onafhankelijk van elkaar kunnen draaien, en (traploos) regelbaar zijn in snelheid en draairichting.

int powerLeft = 0;
    int powerRight = 0;

    if (output >= 0) {
      powerLeft = constrain(params.power + params.diff * output, -255, 255);
      powerRight = constrain(powerLeft - output, -255, 255);
      powerLeft = powerRight + output;
    } else {
      powerRight = constrain(params.power - params.diff * output, -255, 255);
      powerLeft = constrain(powerRight + output, -255, 255);
      powerRight = powerLeft - output;
    }

    analogWrite(MotorRightForward, powerLeft > 0 ? powerLeft : 0);
    analogWrite(MotorRightBackward, powerLeft < 0 ? -powerLeft : 0);
    analogWrite(MotorLeftForward, powerRight > 0 ? powerRight : 0);
    analogWrite(MotorLeftBackward, powerRight < 0 ? -powerRight : 0);
  }
