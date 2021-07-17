/*

Name:                   Jamilu Salisu
Registration Number:    CST/19/SWE/00409
Course:                 Software Construction - SWE2210

System Implemented:     Visitors Management System
Date of submission:     Saturday, July 17, 2021

Features of the system implemented are as follows:
- Pre-booking allows visitors and guests to pre-register prior to arriving.
- Check-In Workflows for different visitor types such as; interview, etc.
- Sign digital forms to improve data security and reduce manual labour process
- Notify hosts instantly and communication to awaiting visitor of their status
- Peace of mind to organization and everyone who enters their workplace
- Making hosting of visitors seamless

*/

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

class VisitorsManagementSystem
{
private:
    string visitorFullName = "";
    string visitorPhoneNumber = "";
    string visitorContactAddress = "";

    string purposeOfVisiting = "";
    string dateOfVisiting = "";
    string timeOfVisiting = "";

    const string visitingPurpose[6] = {
        "Complain",
        "Interview",
        "Meeting",
        "Personal",
        "Repair",
        "Other"};
    const string visitingTime[9] = {
        "10:00am - 10:30am",
        "10:30am - 11:00am",
        "11:00am - 11:30am",
        "11:30am - 12:00pm",
        "12:00pm - 12:30pm",
        "1:30pm - 2:00pm",
        "2:00pm - 2:30pm",
        "2:30pm - 3:00pm",
        "3:00pm - 3:30pm",
    };

    //Index[1]: 'Pending' by default for every request
    const string visitProgress[3] = {
        "Approved",
        "Pending",
        "Rejected"};
    string visitRequestStatus = visitProgress[1]; //set to Pending by default
    int userResponse = 0;

    void visitorPersonalInformation(string name, string phone, string address)
    {
        visitorFullName = name;
        visitorPhoneNumber = phone;
        visitorContactAddress = address;
    }

    void setDateOfVisiting()
    {
        //get and print today's date
        time_t curr_time;
        tm *curr_tm;
        char date_string[100];

        time(&curr_time);
        curr_tm = localtime(&curr_time);
        //format: day month, -year
        strftime(date_string, 50, "%d %B, %Y", curr_tm);

        dateOfVisiting = date_string;
        cout << dateOfVisiting;
    }

    void setVisitStatus(string passwordEntered)
    {
        //wrong password attempt
        //int passwordTrialAttemp = 3;

        if (passwordEntered == "admin")
        {
            cout << "\nAccess granted! Please confirm the visiting status:\n";
            cout << "1. Let the visitor in. \n2. Deny visitor access." << endl;

            cout << "Reply: ";
            cin >> userResponse;

            if (userResponse == 1)
            {
                //set selected option if reply is within option range
                visitRequestStatus = visitProgress[0];
                sendApprovalOrRejectionNotification();
            }
            else if (userResponse == 2)
            {
                visitRequestStatus = visitProgress[2];
                sendApprovalOrRejectionNotification();
            }
            else
            {
                printErrorOnUserReply();
                //Re-run when user input invalid character (recurrence)
                setVisitStatus(passwordEntered);
            }
        }
        else
        {
            /*for (int trialAttemp=3; trialAttemp > 0; trialAttemp--) {
                cout << "Invalid authorization code, please try again.\n\n";
                loginAsSecretaryOrReceptionist();
            } */
            cout << "You\'re not authorized to get access!\n";
        } //end of authenticating authorized code

    } //end of setVisitStatus

    void sendApprovalOrRejectionNotification()
    {
        string message;

        cout << "\n...sending notification to " << visitorPhoneNumber << endl;

        if (visitRequestStatus == "Approved")
        {
            message = ", we\'re pleased to inform you that your request "
                      "has been APPROVED.";
        }
        else
        {
            message = ", after reviewing your request, we have determined "
                      "that it would not be possible to accommodate your "
                      "request at this time and therefore, it\'s denied.";
        }
        cout << "Dear " << getVisitorFullName() << message << endl;

    } //end of printVisitRequestNotification

public:
    //prompt and set visitor's personal information
    void setVisitorPersonalInformation()
    {
        string full_name, phone_number, contact_address;

        cout << "Enter visitor\'s full name: ";
        getline(cin, full_name);

        cout << "Enter visitor\'s phone number: ";
        getline(cin, phone_number);

        cout << "Enter visitor\'s contact address: ";
        getline(cin, contact_address);

        visitorPersonalInformation(full_name, phone_number, contact_address);
    } //end of setVisitorPersonalInformation

    string getVisitorFullName()
    {
        return visitorFullName;
    }

    string getVisitorPhoneNumber()
    {
        return visitorPhoneNumber;
    }

    string getVisitorContactAddress()
    {
        return visitorContactAddress;
    }

    //prompt for visiting purpose
    void setPurposeOfVisiting()
    {
        //display options for user to select
        cout << "\nPlease select purpose of visit:\n";
        for (int i = 0; i < 6; i++)
        {
            cout << i + 1 << ". " << visitingPurpose[i] << "\n";
        }

        cout << "Reply: ";
        cin >> userResponse;

        if (userResponse < 6 && userResponse >= 1)
        {
            //set if selected option is within option range
            purposeOfVisiting = visitingPurpose[userResponse - 1];
        }
        else if (userResponse == 6)
        {
            //prompt and set user input if he/she selected 'other'
            cout << "Please enter purpose of visiting: ";
            cin >> purposeOfVisiting;
        }
        else
        {
            printErrorOnUserReply();
            //Re-run when user input invalid character (recurrence)
            setPurposeOfVisiting();
        }
    } //end of setPurposeOfVisiting

    string getPurposeOfVisiting()
    {
        return purposeOfVisiting;
    }

    //prompt for time of visiting
    void setTimeOfVisiting()
    {
        //display options for user to select
        cout << "\nPlease choose convenient time (Duration: 30min) of visit:\n";
        for (int i = 0; i < 9; i++)
        {
            cout << i + 1 << ". " << visitingTime[i] << "\n";
        }

        cout << "Reply: ";
        cin >> userResponse;

        if (userResponse < 10 && userResponse >= 1)
        {
            //set selected option if reply is within option range
            timeOfVisiting = visitingTime[userResponse - 1];
        }
        else
        {
            printErrorOnUserReply();
            //Re-run when user input invalid character (recurrence)
            setTimeOfVisiting();
        }
    } //end of setTimeOfVisiting

    string getTimeOfVisiting()
    {
        return timeOfVisiting;
    }

    //display when an option is out of range
    void printErrorOnUserReply()
    {
        cout << "Invalid response! Please reply with valid option." << endl;
    }

    void printVisitRequestNotification()
    {
        cout << "Dear " << getVisitorFullName() << ", your request has been submitted successful.\n";
    } //end of printVisitRequestNotification

    void checkVisitorRequestStatus()
    {
        cout << "\nFull name: "
             << "\t\t" << getVisitorFullName() << "\nPhone number: "
             << "\t\t" << getVisitorPhoneNumber() << "\nContact address: "
             << "\t" << getVisitorContactAddress() <<

            "\nPurpose of visiting: "
             << "\t" << getPurposeOfVisiting() << "\nTime of visiting: "
             << "\t"
             << "on ";
        setDateOfVisiting();

        cout << " from " << getTimeOfVisiting() << "\nRequest status: "
             << "\t" << getVisitRequestStatus() << "";

        cout << "\n---------------------------------------------------------";
    } //end of reviewVisitorRequest

    void loginAsSecretaryOrReceptionist()
    {
        string password;
        cout << "Please enter authorization code to get access (hint: admin): ";
        cin >> password;
        setVisitStatus(password);
    }

    string getVisitRequestStatus()
    {
        return visitRequestStatus;
    }
};

int main()
{
    // Creating an object of Visitors
    VisitorsManagementSystem person1;

    cout << "### Step A: Personal Details ###\n";
    person1.setVisitorPersonalInformation();

    cout << "\n### Step B: Visit Schedule ###";
    person1.setPurposeOfVisiting();
    person1.setTimeOfVisiting();

    cout << "\n";
    person1.printVisitRequestNotification();
    person1.checkVisitorRequestStatus();

    cout << "\n### System Admin: Login as Secretary or Receptionist manage request ###\n";
    person1.loginAsSecretaryOrReceptionist();
    person1.checkVisitorRequestStatus();

    return 0;
}
