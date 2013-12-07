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

        // Form for addint a new car to the Database
        public RegisterNewCarForm(ref DataManager _dataManager)
        {
            InitializeComponent();
            dataManager = _dataManager;
            registerPadMessageLabel.Text = "Please enter the vehicle ID number and the radio ID number in HEX.";
            registerPadMessageLabel.ForeColor = Color.Blue;
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

                // Check vehicle ID
                if (vehicleIDTextBox.Text != "")
                {
                    if (!isHEX(vehicleIDTextBox.Text))
                    {
                        registerPadMessageLabel.ForeColor = Color.Red;
                        registerPadMessageLabel.Text = "Vehicle ID must be a HEX value.";
                        return;
                    }

                    if (isInDB(vehicleIDTextBox.Text))
                    {
                        registerPadMessageLabel.Text = "The vehicle ID entered already exists in the database.";
                    }
                }
                else 
                {
                    registerPadMessageLabel.Text = "Invalid vehicle ID.";
                    return;
                }
                
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
                

                newCar = new Car(vehicleIDTextBox.Text, radioIDTextBox.Text);
                registerPadMessageLabel.ForeColor = Color.Blue;
                registerPadMessageLabel.Text = "Vehicle ID and Radio ID successfully verified.";
                registerPadLabel.Text = "Place vehicle on Charging Pad 1 and click OK.";
                regState++;
                
            }

            // Get color information from pad 1
            else if (regState == 1)
            {
                // send Get Color command for Pad 1 and wait for 
                //newCar.pad1Color = dataManager.getPad1Color();
                if (newCar.pad1Color == null)
                {
                    registerPadMessageLabel.Text = "Error getting Pad 1 color information.";
                }
                else
                {
                    registerPadMessageLabel.ForeColor = Color.Blue;
                    registerPadMessageLabel.Text = "Pad 1 color registered successfully.";
                    registerPadLabel.Text = "Place vehicle on Charging Pad 2 and click OK.";
                    regState++;
                }
            }

            // Get color information from pad 2
            else if (regState == 2)
            {
                // send Get Color command for Pad 2 and wait for 
                //newCar.pad2Color = dataManager.getPad2Color();
                if (newCar.pad1Color == null)
                {
                    registerPadMessageLabel.Text = "Error getting Pad 2 color information.";
                }
                else
                {
                    registerPadMessageLabel.ForeColor = Color.Blue;
                    registerPadMessageLabel.Text = "Pad 2 color registered successfully.";
                    registerPadLabel.Text = "Place vehicle on Charging Pad 3 and click OK.";
                    regState++;
                }
            }

            // Get color information from pad 3
            else if (regState == 3)
            {
                // send Get Color command for Pad 3 and wait for 
                //newCar.pad3Color = dataManager.getPad3Color();
                if (newCar.pad1Color == null)
                {
                    registerPadMessageLabel.Text = "Error getting Pad 1 color information.";
                }
                else
                {
                    registerPadMessageLabel.ForeColor = Color.Blue;
                    registerPadMessageLabel.Text = "Pad 1 color registered successfully.";
                    // TODO: try to add the car to the database
                    // TODO: verify the car is now in the database
                    registerPadLabel.Text = "";
                    regState = 0;
                }
            }
            
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
       
    }
}
