using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InductiveCharging
{
    public partial class RegisterNewCarForm : Form
    {

        Car newCar;
        int regState = 0;
        DataManager dataManager;
        public Color messageColor;
        public string messageText;
        public string infoText;
        public bool buttonState;

        // Form for addint a new car to the Database
        public RegisterNewCarForm(ref DataManager _dataManager)
        {
            InitializeComponent();
            dataManager = _dataManager;
            registerPadMessageLabel.Text = "Please enter the vehicle ID number and the radio ID number in HEX.";
            registerPadMessageLabel.ForeColor = Color.Blue;
        }

        private void setMessage(object sender, EventArgs e)
        {
            registerPadMessageLabel.ForeColor = messageColor;
            registerPadMessageLabel.Text = messageText;
            registerCarButton.Enabled = buttonState;
            if (infoText != null)
            {
                registerPadLabel.Text = infoText;
            }

        }

        // Leads the user through registering a new car, including adding the new car to the
        // Database, getting vehicle ID, radio ID and color readings from all three
        // Charging Pads
        // State 0 => Enter vehicle ID and radio ID, build car object and prompt to place vehicle on Pad 1
        // State 1 => send Get Color command to base station for Pad 1, add response to new car & prompt
        //   to place vehicle on Pad 2
        // State 2 => send Get Color command to base station for Pad 2, add response to new car & prompt 
        //   to place vehicle on Pad 3
        // State 3 => Send Get Color command to base station for Pad 3, add response to new car, add car
        //   to database, send confirmation message to user and send Car Info to base station
        private void registerColorButton_Click(object sender, EventArgs e)
        {
            if (regState == 0)
            {
                // reset message
                registerPadMessageLabel.Text = "";

                // Check radio ID
                if (radioIDTextBox.Text != "")
                {
                    if (!isHEX(radioIDTextBox.Text))
                    {
                        registerPadMessageLabel.ForeColor = Color.Red;
                        registerPadMessageLabel.Text = "Radio ID must be a HEX value.";
                        return;
                    }
                }
                else 
                {
                    registerPadMessageLabel.Text = "Invalid radio ID.";
                    return;
                }
                

                newCar = new Car(radioIDTextBox.Text);
                dataManager.registeringCar(ref newCar);
                registerPadMessageLabel.ForeColor = Color.Blue;
                registerPadMessageLabel.Text = "Vehicle ID and Radio ID successfully verified.";
                registerPadLabel.Text = "Place vehicle on Charging Pad 1 and click OK.";
                regState++;
                
            }

            // Get color information from pad 1
            else if (regState == 1)
            {
                dataManager.colorChangedEvent += gotNewColorEvent;

                // send Get Color command for Pad 1 and wait for 
                dataManager.sendCommand("GC P1");

                registerPadMessageLabel.Text = "Getting Pad 1 color information...";

                registerCarButton.Enabled = false;
            }

            // Get color information from pad 2
            else if (regState == 2)
            {
                dataManager.colorChangedEvent += gotNewColorEvent;

                dataManager.sendCommand("GC P2");

                registerPadMessageLabel.Text = "Getting Pad 2 color information...";

                registerCarButton.Enabled = false;
            }

            // Get color information from pad 3
            else if (regState == 3)
            {
                dataManager.colorChangedEvent += gotNewColorEvent;

                dataManager.sendCommand("GC P3");

                registerPadMessageLabel.Text = "Getting Pad 3 color information...";

                registerCarButton.Enabled = false;
            }
            
            // Get one more click from user acknowledging successful registration
            else if (regState == 4)
            {
                regState = 0;
                dataManager.carRegistrationComplete();
                this.Close();
            }
        }

        private void gotNewColorEvent()
        {
            int red, green, blue;
            if (regState == 1)
            {
                if (newCar.pad1Color.red == null || newCar.pad1Color.green == null || newCar.pad1Color.blue == null)
                {
                    messageText = "Error getting Pad 1 color information.";
                }
                else if (int.TryParse(newCar.pad1Color.red, out red) && int.TryParse(newCar.pad1Color.blue, out blue) && int.TryParse(newCar.pad1Color.green, out green))
                {
                    if ((red > 950 && green > 950 && blue > 950) || red + green + blue < 300)
                    {
                        messageColor = Color.Red;
                        messageText = "Pad 1 color invalid.";
                    }
                    else
                    {
                        messageColor = Color.Blue;
                        messageText = "Pad 1 color registered successfully.";
                        infoText = "Place vehicle on Charging Pad 2 and click OK.";
                        regState++;
                    }
                }
                else
                {
                    messageColor = Color.Red;
                    messageText = "Pad 1 color string parse error.";
                }
                
                
                buttonState = true;
                dataManager.colorChangedEvent -= gotNewColorEvent;
            }
            else if (regState == 2)
            {
                if (newCar.pad2Color.red == null || newCar.pad2Color.green == null || newCar.pad2Color.blue == null)
                {
                    messageText = "Error getting Pad 2 color information.";
                }
                else if (int.TryParse(newCar.pad2Color.red, out red) && int.TryParse(newCar.pad2Color.blue, out blue) && int.TryParse(newCar.pad2Color.green, out green))
                {
                    if ((red > 950 && green > 950 && blue > 950) || red + green + blue < 300)
                    {
                        messageColor = Color.Red;
                        messageText = "Pad 2 color invalid.";
                    }
                    else
                    {
                        messageColor = Color.Blue;
                        messageText = "Pad 2 color registered successfully.";
                        infoText = "Place vehicle on Charging Pad 3 and click OK.";
                        regState++;
                    }
                }
                else
                {
                    messageColor = Color.Red;
                    messageText = "Pad 2 color string parse error.";
                }
                buttonState = true;
                dataManager.colorChangedEvent -= gotNewColorEvent;
            }

         // Get color information from pad 3
            else if (regState == 3)
            {
                if (newCar.pad3Color.red == null || newCar.pad3Color.green == null || newCar.pad3Color.blue == null)
                {
                    messageText = "Error getting Pad 3 color information.";
                }
                else if (int.TryParse(newCar.pad3Color.red, out red) && int.TryParse(newCar.pad3Color.blue, out blue) && int.TryParse(newCar.pad3Color.green, out green))
                {
                    if ((red > 950 && green > 950 && blue > 950) || red + green + blue < 300)
                    {
                        messageColor = Color.Red;
                        messageText = "Pad 3 color invalid.";
                    }
                    else
                    {
                        messageColor = Color.Blue;
                        messageText = "Pad 3 color registered successfully.";
                        infoText = "New car registered successfully.";
                        regState++;
                    }
                }
                else
                {
                    messageColor = Color.Red;
                    messageText = "Pad 3 color string parse error.";
                }
                buttonState = true;
                dataManager.colorChangedEvent -= gotNewColorEvent;
            }
            this.Invoke(new EventHandler(setMessage));
        }


        // Checks a string to see if it can be a legitimate HEX number and returns true if it can
        private bool isHEX(string s)
        {
            char[] hexChars = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
            char[] chars = s.ToCharArray();
            foreach (char c in chars)
            {
                if (!hexChars.Contains(c)) return false;
            }
            return true;
        }

        // Determines whether a carID is already in the Database and returns true if it is
        private bool isInDB(string s)
        {
            //TODO
            return false;
        }

        private void registerCarCancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
       
    }
}
