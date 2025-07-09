#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// <1 main login system>
// Function prototypes
void login();
void logout();
int authenticateUser(char *username, char *password, char *role);
int admin_system();
int hotel_staff_system();
void guestMenu();
void customerMenu();

int main ()
{
    int menu_choice;
    do
    {
        int menu_choice, login_status;
        printf ("___________________________\n");
        printf ("|1. Administrator         |\n");
        printf ("|2. Hotel Staff           |\n");
        printf ("|3. Customer              |\n");
        printf ("|4. Guest                 |\n");
        printf ("|5. Exit                  |\n");
        printf ("___________________________\n");

        printf ("Choose your role: ");
        scanf(" %d", &menu_choice);

        if (menu_choice == 1)
        {
            login();
            admin_system();

            // if okay then admin menu
            // admin_system
        }

        else if (menu_choice == 2)
        {
            login ();
            hotel_staff_system();
            // if okay then hotel staff menu
        }

        else if (menu_choice == 3)
        {
            login();
            customerMenu();
            // if okay then customer menu
        }

        else if (menu_choice == 4)
        {
            guestMenu();
        }

        else 
        {
            printf("Invalid choice \n");
        }        

    } while (menu_choice != 5);
    

}

/// login portion
#include <stdlib.h>
#include <string.h>

#define USERS_FILE "users.txt"

// Function to handle user login
void login() {
    char username[50];
    char password[50];
    char role[20];


    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int authenticated = authenticateUser(username, password, role);

    if (authenticated) {
        printf("Login successful! Welcome, %s (%s).\n", username, role);
        // Proceed to the appropriate menu based on role
        if (strcmp(role, "staff") == 0) {
            // Call staff menu function
        } else if (strcmp(role, "customer") == 0) {
            // Call customer menu function
        }
        /// i dont think we need this logout();
    } 
    else 
    {
        system("cls");
        printf("Invalid username or password.\n");
        exit(0);
    }
}

// Function to handle user logout
void logout() 
{
    printf("You have been logged out.\n");
}

// Function to authenticate user
int authenticateUser(char *username, char *password, char *role) 
{

    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) 
    {
        char file_username[50], file_password[50], file_role[20];
        sscanf(line, "%[^,],%[^,],%s", file_username, file_password, file_role);

        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) 
        {
            strcpy(role, file_role);
            fclose(file);
            return 1;
        }
    }

    fclose(file);
}
////////////////////

///////////////////////////////////////////////////////////////////////////////////////  <2. admin menu>
#define USERS_FILE "users.txt"
#define ROOMS_FILE "rooms.txt"

// Structure definitions

// Updated User Structure
struct User {
    char username[50];
    char password[50];
    char role[20];
};

// Updated Room Structure
struct Room {
    int room_number;
    char room_status[20];  // Replacing room_type with room_status
    char availability[20];
    int room_capacity;
    double room_rate;
};

// Function prototypes

void displayMenu();
void registerUser();
void updateUserStatus();
void viewUsers();
void deleteUser();
void addOrUpdateRoom(int isUpdate);
void updateRoomStatus();
void removeRoom();
void viewRooms();

// Function to display menu

void displayMenu() {
    printf("\nAdministrator Menu:\n");
    printf("1. Register new user\n");
    printf("2. Update user status\n");
    printf("3. View users\n");
    printf("4. Delete user\n");
    printf("5. Add new room\n");
    printf("6. Update room info\n");
    printf("7. Remove room\n");
    printf("8. View rooms\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

// Function to register a new user

void registerUser() {
    struct User newUser;

    printf("\nEnter username: ");
    scanf("%s", newUser.username);

    printf("Enter password: ");
    scanf("%s", newUser.password);

    printf("Enter role (staff/customer): ");
    scanf("%s", newUser.role);

    FILE *file = fopen(USERS_FILE, "a");
    if (file == NULL) {
        printf("Error opening file %s.\n", USERS_FILE);
        return;
    }

    fprintf(file, "%s,%s,%s\n", newUser.username, newUser.password, newUser.role);
    fclose(file);

    printf("User %s registered successfully.\n", newUser.username);
}

// Function to update user status

void updateUserStatus() {
    char username[50];
    char new_role[20];
    int found = 0;

    printf("Enter username to update: ");
    scanf("%s", username);

    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", USERS_FILE);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temp file.\n");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char current_username[50], password[50], role[20];
        sscanf(line, "%[^,],%[^,],%s", current_username, password, role);

        if (strcmp(current_username, username) == 0) {
            found = 1;
            printf("Enter new role for %s (staff/customer): ", username);
            scanf("%s", new_role);
            fprintf(tempFile, "%s,%s,%s\n", username, password, new_role);
            printf("User %s updated successfully.\n", username);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    if (!found) {
        printf("User %s not found.\n", username);
    }

    fclose(file);
    fclose(tempFile);

    remove(USERS_FILE);
    rename("temp.txt", USERS_FILE);
}

// Function to delete a user

// Function to delete a user
void deleteUser() {
    char username[50];
    int found = 0;

    printf("\nEnter username to delete: ");
    scanf("%s", username);

    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", USERS_FILE);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temp file.\n");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char fileUsername[50], password[50], role[20], status[20];
        sscanf(line, "%[^,],%[^,],%[^,],%s", fileUsername, password, role, status);

        if (strcmp(fileUsername, username) == 0) {
            found = 1;
            printf("User %s deleted successfully.\n", username);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the old file with the new file
    remove(USERS_FILE);
    rename("temp.txt", USERS_FILE);

    if (!found) {
        printf("User %s not found.\n", username);
    }
}

// Function to view all users

// Function to view all users
// Function to view all users
void viewUsers() {
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", USERS_FILE);
        return;
    }

    printf("\nList of Users:\n");
    printf("----------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char username[50], password[50], role[20];

        // Parse the line according to the format username,password,role
        if (sscanf(line, "%49[^,],%49[^,],%19s", username, password, role) == 3) {
            printf("Username: %s\n", username);
            printf("Password: %s\n", password);
            printf("Role: %s\n", role);
        } else {
            printf("Error reading user data.\n");
        }

        printf("----------------------------------------\n");
    }

    fclose(file);
}


// Function to add or update a room

// Function to add or update room information
void addOrUpdateRoom(int isUpdate) {
    struct Room room;
    int roomNumber;
    int found = 0;

    if (isUpdate) {
        printf("\nEnter room number to update: ");
        scanf("%d", &roomNumber);

        FILE *file = fopen(ROOMS_FILE, "r");
        if (file == NULL) {
            printf("Error opening file %s.\n", ROOMS_FILE);
            return;
        }

        FILE *tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Error opening temp file.\n");
            fclose(file);
            return;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            int tempRoomNumber;
            char tempStatus[20], tempAvailability[20];
            int tempCapacity;
            double tempRate;

            sscanf(line, "%d,%[^,],%[^,],%d,%lf", &tempRoomNumber, tempStatus, tempAvailability, &tempCapacity, &tempRate);

            if (tempRoomNumber == roomNumber) {
                printf("Enter new room status (occupied/unoccupied/maintenance): ");
                scanf("%s", room.room_status);

                printf("Enter new room availability (available/unavailable): ");
                scanf("%s", room.availability);

                printf("Enter new room capacity: ");
                scanf("%d", &room.room_capacity);

                printf("Enter new room rate per night: ");
                scanf("%lf", &room.room_rate);

                fprintf(tempFile, "%d,%s,%s,%d,%lf\n", roomNumber, room.room_status, room.availability, room.room_capacity, room.room_rate);
                found = 1;
                printf("Room %d updated successfully.\n", roomNumber);
            } else {
                fprintf(tempFile, "%s", line);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove(ROOMS_FILE);
        rename("temp.txt", ROOMS_FILE);

        if (!found) {
            printf("Room %d not found.\n", roomNumber);
        }
    } else {
        printf("\nEnter room number: ");
        scanf("%d", &room.room_number);

        printf("Enter room status (occupied/unoccupied/maintenance): ");
        scanf("%s", room.room_status);

        printf("Enter room availability (available/unavailable): ");
        scanf("%s", room.availability);

        printf("Enter room capacity: ");
        scanf("%d", &room.room_capacity);

        printf("Enter room rate per night: ");
        scanf("%lf", &room.room_rate);

        FILE *file = fopen(ROOMS_FILE, "a");
        if (file == NULL) {
            printf("Error opening file %s.\n", ROOMS_FILE);
            return;
        }

        fprintf(file, "%d,%s,%s,%d,%lf\n", room.room_number, room.room_status, room.availability, room.room_capacity, room.room_rate);
        fclose(file);

        printf("Room %d added successfully.\n", room.room_number);
    }
}

// Function to remove a room

void removeRoom() {
    int room_number;
    int found = 0;

    printf("Enter room number to remove: ");
    scanf("%d", &room_number);

    FILE *file = fopen(ROOMS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", ROOMS_FILE);
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temp file.\n");
        fclose(file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int rn;
        sscanf(line, "%d", &rn);

        if (rn == room_number) {
            found = 1;
            printf("Room %d removed successfully.\n", room_number);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    if (!found) {
        printf("Room %d not found.\n", room_number);
    }

    fclose(file);
    fclose(tempFile);

    remove(ROOMS_FILE);
    rename("temp.txt", ROOMS_FILE);
}

// Function to view all rooms

void viewRooms() {
    FILE *file = fopen(ROOMS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file %s.\n", ROOMS_FILE);
        return;
    }

    printf("\nList of Rooms:\n");
    printf("----------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int room_number, room_capacity;
        char room_status[20], availability[20];
        double room_rate;
        sscanf(line, "%d,%[^,],%[^,],%d,%lf\n", &room_number, room_status, availability, &room_capacity, &room_rate);

        printf("Room Number: %d\n", room_number);
        printf("Room Status: %s\n", room_status);
        printf("Availability: %s\n", availability);
        printf("Room Capacity: %d\n", room_capacity);
        printf("Room Rate: %.2lf\n", room_rate);
        printf("----------------------------------------\n");
    }

    fclose(file);
}

// ADMIN SYSTEM
int admin_system () {
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume newline character after scanf

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                updateUserStatus();
                break;
            case 3:
                viewUsers();
                break;
            case 4:
                deleteUser();
                break;
            case 5:
                addOrUpdateRoom(0);
                break;
            case 6:
                addOrUpdateRoom(1);
                break;
            case 7:
                removeRoom();
                break;
            case 8:
                viewRooms();
                break;
            case 9:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////// <3. hotel staff system>

// manage room reservation
int manage_rsv()
{

    # define og_filename "reservations.txt"
    # define temp_filename "temp.txt"
    int option,chosen_rsv_id;

    // ask for reservation ID 
    printf("Enter reservation ID to make any updates: ");
    scanf(" %d", &chosen_rsv_id);

    // menu for manage reservations 
    printf("1. update Reservation Status \n");
    printf("2. update Room Number \n");
    printf("3. update check in & check out date \n");

    printf("To manage customer reservation, choose option: ");
    scanf(" %d", &option);
    
    // MAKE SURE TO MATCH IT TO THE RESERVATION ID

    if (option == 1)
    {
        // update room reservation status ; reserved unreserved

        // reservations.txt & temp.txt

        FILE *file, *tempfile;
        char line [256]; // buffer size is 256, used to read lines
        int found = 0;
        char rs_chosen;

        // open original file + temporary file
        file = fopen(og_filename, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }

        tempfile = fopen(temp_filename, "w");
        if (tempfile == NULL)
        {
            perror("Error opening temp file");
            fclose(file);
            return 1;
        }

        // ask user for the new reservation status
        printf("To update reservation status to Reserved enter [r], to update to unreserved enter [u]: ");
        scanf(" %c", &rs_chosen);


        // process each line in the file

        while(fgets(line, sizeof(line), file) != NULL)
        {
            int rsv_id, cust_id, room_num, ci_date, co_date, gs_charge;
            char rs_status[20];
            char gs_status[20];

            // read reservation id, status, room number, check in and check out from the line
            sscanf(line, "%d,%d,%19[^,],%19[^,],%d,%d,%d,%d", &rsv_id, &cust_id, rs_status, gs_status, &room_num, &ci_date, &co_date, &gs_charge);

            // if id matches update rs status
            if (rsv_id == chosen_rsv_id)
            {
                found = 1;
                if (rs_chosen == 'r')
                {
                    // update to reserved
                    sprintf(line, "%d,%d,reserved,%s,%d,%d,%d,%d\n", rsv_id, cust_id, gs_status, room_num, ci_date, co_date, gs_charge);
                    printf("Reservation status has successfully been updated to Reserved. \n");
                }

                else if (rs_chosen == 'u')
                {
                    // update to unreserved
                    sprintf(line, "%d,%d,unreserved,%s,%d,%d,%d,%d\n", rsv_id, cust_id, gs_status, room_num, ci_date, co_date, gs_charge);
                    printf("Reservation status has successfully been updated to Unreserved. \n");
                }

            }
            
            // write the line unchanged to the temporary file
            fputs(line,tempfile);
            
        }

        if (!found) 
        {
            printf("Reservation ID %d not found. \n", chosen_rsv_id);
        }

        // closing the files
        fclose(file);
        fclose(tempfile);

        // replacing original file with the updated temporary file
        remove(og_filename);
        rename(temp_filename, og_filename);

        return 0;

    }


    else if (option == 2)
    {
        // update room number of the reservation 10x

        FILE *file, *tempfile;
        char line [256]; // buffer size is 256, used to read lines
        int found = 0;
        int cur_rn, new_rn;

        // open original file + temporary file
        file = fopen(og_filename, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }

        tempfile = fopen(temp_filename, "w");
        if (tempfile == NULL)
        {
            perror("Error opening temp file");
            fclose(file);
            return 1;
        }


        //ask user input for new room num
        printf("Enter updated room number: ");
        scanf(" %d", &new_rn);

        // reading all the lines & parsing
        while(fgets(line, sizeof(line), file) != NULL)
        {
            int rsv_id, cust_id, room_num, ci_date, co_date, gs_charge;
            char rs_status[20];
            char gs_status[20];

            // read reservation id, customer id, reservation status, guest status, room number, check in date, check out date, guest charge
            sscanf(line, "%d,%d,%19[^,],%19[^,],%d,%d,%d,%d", &rsv_id, &cust_id, rs_status, gs_status, &room_num, &ci_date, &co_date, &gs_charge);


            // if id chosen matches an id in the text file
            if (rsv_id == chosen_rsv_id)
            {
                // change room number
                found = 1;
                sprintf(line, "%d,%d,%s,%s,%d,%d,%d,%d\n", rsv_id, cust_id, rs_status, gs_status, new_rn, ci_date, co_date, gs_charge);
                printf("The room number has been successfully updated to %d.\n", new_rn);

            }
            
            // write the line unchanged to the temporary file
            fputs(line,tempfile);
        }

        // if reservation id isnt found
        if (!found) 
        {
            printf("Reservation ID %d not found. \n", chosen_rsv_id);
        }

        // closing the files
        fclose(file);
        fclose(tempfile);

        // replacing original file with the updated temporary file
        remove(og_filename);
        rename(temp_filename, og_filename);

        return 0;

    }

    else if (option == 3)
    {
        // update check in, check out and immediately change the guest charge
        int new_ci_date, new_co_date, new_gs_charge, stay_duration;
        printf("Enter updated check in date: ");
        scanf("%d", &new_ci_date);

        printf("Enter updated check out date: ");
        scanf("%d", &new_co_date);

        // amount of days = co - ci
        stay_duration = new_co_date - new_ci_date;

        // guest charge = stay duration * room rate
        // assume room rate = 50
        // calculate guest charge and then update into text file
        new_gs_charge = stay_duration * 50;

        // text file handling
        FILE *file, *tempfile;
        char line [256]; // buffer size is 256, used to read lines
        int found = 0;
        int cur_rn, new_rn;

        // open original file + temporary file
        file = fopen(og_filename, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            return 1;
        }

        tempfile = fopen(temp_filename, "w");
        if (tempfile == NULL)
        {
            perror("Error opening temp file");
            fclose(file);
            return 1;
        }

        // reading all the lines & parsing
        while(fgets(line, sizeof(line), file) != NULL)
        {
            int rsv_id, cust_id, room_num, ci_date, co_date, gs_charge;
            char rs_status[20];
            char gs_status[20];

            // read reservation id, customer id, reservation status, guest status, room number, check in date, check out date, guest charge
            sscanf(line, "%d,%d,%19[^,],%19[^,],%d,%d,%d,%d", &rsv_id, &cust_id, rs_status, gs_status, &room_num, &ci_date, &co_date, &gs_charge);


            // if id chosen matches an id in the text file
            if (rsv_id == chosen_rsv_id)
            {
                // change ci_date, co_date, gs_charge
                found = 1;
                sprintf(line, "%d,%d,%s,%s,%d,%d,%d,%d\n", rsv_id, cust_id, rs_status, gs_status, room_num, new_ci_date, new_co_date, new_gs_charge);
                printf("Check in date & Check out date has been updated, New guest charge is %d\n", new_gs_charge);

            }
            
            // write the line unchanged to the temporary file
            fputs(line,tempfile);
        }

        // if reservation id isnt found
        if (!found) 
        {
            printf("Reservation ID %d not found. \n", chosen_rsv_id);
        }

        // closing the files
        fclose(file);
        fclose(tempfile);

        // replacing original file with the updated temporary file
        remove(og_filename);
        rename(temp_filename, og_filename);

        return 0;

    }
    else
    {
        printf("Invalid Choice. \n");
    }

}

// check in check out guests
int check_inout()
{
    # define og_filename "reservations.txt"
    # define temp_filename "temp.txt"

    char option_gs;
    int chosen_rsv_id;
    // ask for reservation id to specifically change that line of the text file
    // use RSV_ID to match in the text file
    printf("To check in / check out guest, enter reservationID: ");
    scanf(" %d", &chosen_rsv_id);


    // search the text file for current guest status and equate to cur_gs
    printf("Enter [i] to update guest status to checked in, Enter [o] to update guest status to checked out: ");
    scanf(" %s", &option_gs);

    // text file handling
    // reservations.txt & temp.txt

    FILE *file, *tempfile;
    char line [256]; // buffer size is 256, used to read lines
    int found = 0;

    // open original file + temporary file
    file = fopen(og_filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    tempfile = fopen(temp_filename, "w");
    if (tempfile == NULL)
    {
        perror("Error opening temp file");
        fclose(file);
        return 1;
    }    

    // process each line in the file

    while(fgets(line, sizeof(line), file) != NULL)
    {
        int rsv_id, cust_id, room_num, ci_date, co_date, gs_charge;
        char rs_status[20];
        char gs_status[20];

        // read reservation id, status, room number, check in and check out from the line
        sscanf(line, "%d,%d,%19[^,],%19[^,],%d,%d,%d,%d", &rsv_id, &cust_id, rs_status, gs_status, &room_num, &ci_date, &co_date, &gs_charge);

        // if id matches update rs status
        if (rsv_id == chosen_rsv_id)
        {
            found = 1;
            if (option_gs == 'i')
            {
                // update to checked in
                sprintf(line, "%d,%d,%s,checked in,%d,%d,%d,%d\n", rsv_id, cust_id, rs_status, room_num, ci_date, co_date, gs_charge);
            }

            else if (option_gs == 'o')
            {
                // update to checked out
                sprintf(line, "%d,%d,%s,checked out,%d,%d,%d,%d\n", rsv_id, cust_id, rs_status, room_num, ci_date, co_date, gs_charge);
            }

            else
            {
                printf("Invalid Choice");
            }

        }
            
        // write the line unchanged to the temporary file
        fputs(line,tempfile);
            
    }

    if (!found) 
    {
        printf("Reservation ID %d not found. \n", chosen_rsv_id);
    }

    // closing the files
    fclose(file);
    fclose(tempfile);

    // replacing original file with the updated temporary file
    remove(og_filename);
    rename(temp_filename, og_filename);

    return 0;

}

// view room availability
int view_roomavailability()
{
    # define max_rsv 100
    # define max_rooms 100
    # define og_filename "reservations.txt"

    // 1. defining the structure as rsv_structure
    typedef struct{
        int rsv_id;
        int cust_id;
        char rs_status[20];
        char gs_status[20];
        int room_num;
        int ci_date;
        int co_date;
        int gs_charge;
    } rsv_structure; // this is used as the structure

    rsv_structure reservations[max_rsv]; // an array to store rsv info in a structure as rsv_structure
    int rsv_count = 0 ; // used to count no. reservations read

    // 2. open & read file, then parse & organize
    // this part is just reading the file -> organizing it to fit the rsv_structure -> putting it in the array reservations[]

    FILE *file;
    char line [256]; // buffer to read lines from the file
    file = fopen(og_filename, "r");
    if (file == NULL)
    {
        perror("Error opening the file. ");
        return 1; // exit if there was an error
    }

    //read rsv from the file
    // while loop reads each line in the text file into line
    while (fgets(line, sizeof(line), file))
    {
        if (rsv_count >= max_rsv)
        {
            printf("Maximum number of reservations has reached. \n");
            break;
        }

        // parse & organize
        sscanf(line, "%d,%d,%19[^,],%19[^,],%d,%d,%d,%d", 
        &reservations[rsv_count].rsv_id, 
        &reservations[rsv_count].cust_id, 
        reservations[rsv_count].rs_status, 
        reservations[rsv_count].gs_status,
        &reservations[rsv_count].room_num,
        &reservations[rsv_count].ci_date,
        &reservations[rsv_count].co_date,
        &reservations[rsv_count].gs_charge);

        // increase the rsv_count
        rsv_count++;
    }

    fclose(file);

    // 3. ask for user input & validate it

    int chosen_ci, chosen_co;
    printf("To view room availability \nEnter Check-in date: ");
    scanf(" %d", &chosen_ci);
    printf("Enter check-out date: ");
    scanf(" %d", &chosen_co);

    if (chosen_ci >= chosen_co)
    {
        printf("Check out date must be after the check in date. \n");
        return 1; 
    }

    // 4.checking inside the array file to see the available rooms

    int avail_rooms[max_rooms]; // array is to store the room numbers of available rooms
    int room_count = 0; // this is to store how many rooms are available

    // initializing the avail_rooms array as -1 so it is empty
    for (int i = 0; i < max_rooms; i++)
    {
        avail_rooms[i] = -1;
    }

    // this iterates over all of the reservations read, goes through every single line in the file
    for (int i = 0; i < rsv_count; i++) // 
    {
        // check for overlap
        if (!(chosen_co <= reservations[i].ci_date || chosen_ci >= reservations[i].co_date))
        {
            // this means that the room isnt available, so skip it
            continue;
        }
        int room_found = 0; //flag that will count if the room is found 1 or not 0
        // check if the room is already in the avail_rooms array
        for(int j = 0; j < room_count; j++)
        {
            if (avail_rooms[j] == reservations[i].room_num) // talking about that specific room 
            {
                room_found = 1;
                break;
            }
        }
        // if the room isnt in the list, then add it
        if ( !room_found && room_count < max_rooms)
        {
            avail_rooms[room_count] = reservations[i].room_num ;
            room_count ++;
        }

    }

    // printing available rooms
    if (room_count > 0)
    {
        printf("available rooms for the given date range:\n");
        for (int i = 0; i < room_count; i++)
        {
            printf("Rooms %d\n", avail_rooms[i]);
        }
    }
    else 
    {
        printf("No rooms are available for the given date range.\n");
    }

    return 0;
 
}

// view booking history
int view_bookinghistory()
{
    // ask for room number
    // in reservation txt based on the room number collect all of the information of who has stayed there

    # define max_rsv 100
    # define max_rooms 100
    # define og_filename "reservations.txt"

    // 1. defining the structure as rsv_structure
    typedef struct{
        int rsv_id;
        int cust_id;
        char rs_status[20];
        char gs_status[20];
        int room_num;
        int ci_date;
        int co_date;
        int gs_charge;
    } rsv_structure; // this is used as the structure

    rsv_structure reservations[max_rsv]; // an array to store rsv info in a structure as rsv_structure
    int rsv_count = 0 ; // used to count no. reservations read

    // 2. open & read file, then parse & organize
    // this part is just reading the file -> organizing it to fit the rsv_structure -> putting it in the array reservations[]

    FILE *file;
    char line [256]; // buffer to read lines from the file
    file = fopen(og_filename, "r");
    if (file == NULL)
    {
        perror("Error opening the file. ");
        return 1; // exit if there was an error
    }

    while (fgets(line, sizeof(line), file))
    {
        if (rsv_count >= max_rsv)
        {
            printf("Maximum number of reservations has reached. \n");
            break;
        }

        // parse & organize
        sscanf(line, "%d,%d,%19[^,],%19[^,],%d,%d,%d,%d", 
        &reservations[rsv_count].rsv_id, 
        &reservations[rsv_count].cust_id, 
        reservations[rsv_count].rs_status, 
        reservations[rsv_count].gs_status,
        &reservations[rsv_count].room_num,
        &reservations[rsv_count].ci_date,
        &reservations[rsv_count].co_date,
        &reservations[rsv_count].gs_charge);

        // increase the rsv_count
        rsv_count++;
    }

    fclose(file);

    //  ask for user input and validate it
    int chosen_room_num;

    printf("To view booking history, enter room number: ");
    scanf("%d", &chosen_room_num);

    // print out all of the bookings under the same room number
    int found = 0;
    for (int i = 0; i < rsv_count; i++)
    {
        if (reservations[i].room_num == chosen_room_num)
        {
            printf("Reservation ID: %d\n", reservations[i].rsv_id);
            printf("Customer ID: %d\n", reservations[i].cust_id);
            printf("Reservation Status: %s\n", reservations[i].rs_status);
            printf("Guest Status: %s\n", reservations[i].gs_status);
            printf("Room Number: %d\n", reservations[i].room_num);
            printf("Check In Date: %d\n", reservations[i].ci_date);
            printf("Check Out Date: %d\n", reservations[i].co_date);
            printf("Guest charge: %d\n", reservations[i].gs_charge);
            printf("____________________\n");
            found = 1;   
        }

    }
    if (!found)
    {
        printf("No reservations found for room number %d.\n", chosen_room_num);
    }

    return 0;
}

// hotel staff system

int hotel_staff_system()
{
    int i = 1;
    while (i>0)
    {
        int menu_option;
        printf("_____________________________________\n");
        printf("|1. Manage room reservation         |\n");
        printf("|2. Check in / Check out guest      |\n");
        printf("|3. View room availability          |\n");
        printf("|4. View booking history            |\n");
        printf("|5. Log out                         |\n");
        printf("_____________________________________\n");

        printf("Choose option: ");
        scanf(" %d", &menu_option);

        if (menu_option == 1)
        {
            manage_rsv();
        }

        else if (menu_option == 2)
        {
            check_inout();
        }

        else if (menu_option == 3)
        {
            view_roomavailability();
        }

        else if (menu_option == 4)
        {
            view_bookinghistory();
        }

        else if (menu_option == 5)
        {
            break;
        }

        else
        {
            printf("Invalid Choice");
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////// <4. customer system>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROOMS_FILE "rooms.txt"
#define RESERVATIONS_FILE "reservations.txt"

// Structure definitions

struct Room1 {
    int room_number;
    char room_status[20];
    char availability[20];
    int room_capacity;
    double room_rate;
};

struct Reservation {
    int reservation_id;
    int customer_id;
    char reservation_status[20];
    char guest_status[20];
    int room_number;
    char check_in_date[20];
    char check_out_date[20];
    double guest_charge;
};

// Function prototypes

void customerMenu();
void viewAvailableRooms();
void makeReservation();
void viewReservations();
void cancelReservation();

// Helper function to convert string to lowercase

void strToLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Main function
// Function to display customer menu

void customerMenu() {
    int choice;
    do {
        printf("\nCustomer Menu:\n");
        printf("1. View Available Rooms\n");
        printf("2. Make a Reservation\n");
        printf("3. View My Reservations\n");
        printf("4. Cancel a Reservation\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAvailableRooms();
                break;
            case 2:
                makeReservation();
                break;
            case 3:
                viewReservations();
                break;
            case 4:
                cancelReservation();
                break;
            case 5:
                printf("Exiting Customer menu.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 5);
}

// Function to view available rooms

void viewAvailableRooms() {
    FILE *file = fopen(ROOMS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nAvailable Rooms:\n");
    printf("----------------------------------------\n");

    char line[256]; // Declare line buffer
    while (fgets(line, sizeof(line), file)) {
        struct Room1 room;
        sscanf(line, "%d,%[^,],%[^,],%d,%lf", &room.room_number, room.room_status, room.availability, &room.room_capacity, &room.room_rate);

        // Convert availability to lowercase for comparison
        strToLower(room.availability);

        if (strcmp(room.availability, "available") == 0) {
            printf("Room Number: %d\n", room.room_number);
            printf("Room Status: %s\n", room.room_status);
            printf("Room Capacity: %d\n", room.room_capacity);
            printf("Room Rate: %.2lf\n", room.room_rate);
            printf("----------------------------------------\n");
        }
    }

    fclose(file);
}

// Function to make a reservation

void makeReservation() {
    FILE *roomsFile = fopen(ROOMS_FILE, "r");
    FILE *reservationsFile = fopen(RESERVATIONS_FILE, "a");
    if (roomsFile == NULL || reservationsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int room_number;
    char check_in_date[20];
    char check_out_date[20];
    printf("Enter Room Number to reserve: ");
    scanf("%d", &room_number);
    printf("Enter Check-In Date (YYYY-MM-DD): ");
    scanf("%s", check_in_date);
    printf("Enter Check-Out Date (YYYY-MM-DD): ");
    scanf("%s", check_out_date);

    struct Room1 room;
    int room_found = 0;
    char line[256]; // Declare line buffer
    while (fgets(line, sizeof(line), roomsFile)) {
        sscanf(line, "%d,%[^,],%[^,],%d,%lf", &room.room_number, room.room_status, room.availability, &room.room_capacity, &room.room_rate);

        // Convert availability to lowercase for comparison
        strToLower(room.availability);

        if (room.room_number == room_number && strcmp(room.availability, "available") == 0) {
            room_found = 1;
            break;
        }
    }

    if (room_found) {
        struct Reservation reservation;
        reservation.reservation_id = rand() % 10000; // Generating a random reservation ID
        reservation.customer_id = 1; // For simplicity, assigning a static customer ID
        strcpy(reservation.reservation_status, "reserved");
        strcpy(reservation.guest_status, "checked-in");
        reservation.room_number = room.room_number;
        strcpy(reservation.check_in_date, check_in_date);
        strcpy(reservation.check_out_date, check_out_date);
        reservation.guest_charge = room.room_rate;

        fprintf(reservationsFile, "%d,%d,%s,%s,%d,%s,%s,%lf\n", reservation.reservation_id, reservation.customer_id, reservation.reservation_status, reservation.guest_status, reservation.room_number, reservation.check_in_date, reservation.check_out_date, reservation.guest_charge);

        // Update room availability to "unavailable"
        fclose(roomsFile);
        FILE *roomsFileWrite = fopen(ROOMS_FILE, "r+");
        if (roomsFileWrite == NULL) {
            printf("Error opening file.\n");
            return;
        }

        FILE *tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Error opening file.\n");
            return;
        }

        while (fgets(line, sizeof(line), roomsFileWrite)) {
            struct Room1 tempRoom;
            sscanf(line, "%d,%[^,],%[^,],%d,%lf", &tempRoom.room_number, tempRoom.room_status, tempRoom.availability, &tempRoom.room_capacity, &tempRoom.room_rate);

            if (tempRoom.room_number == room.room_number) {
                strcpy(tempRoom.availability, "unavailable");
            }
            fprintf(tempFile, "%d,%s,%s,%d,%lf\n", tempRoom.room_number, tempRoom.room_status, tempRoom.availability, tempRoom.room_capacity, tempRoom.room_rate);
        }

        fclose(roomsFileWrite);
        fclose(tempFile);
        remove(ROOMS_FILE);
        rename("temp.txt", ROOMS_FILE);
        printf("Reservation made successfully.\n");
    } else {
        printf("Room not available or does not exist.\n");
    }

    fclose(roomsFile);
    fclose(reservationsFile);
}

// Function to view reservations

void viewReservations() {
    FILE *file = fopen(RESERVATIONS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nYour Reservations:\n");
    printf("----------------------------------------\n");

    char line[256]; // Declare line buffer
    while (fgets(line, sizeof(line), file)) {
        struct Reservation reservation;
        sscanf(line, "%d,%d,%[^,],%[^,],%d,%[^,],%[^,],%lf", &reservation.reservation_id, &reservation.customer_id, reservation.reservation_status, reservation.guest_status, &reservation.room_number, reservation.check_in_date, reservation.check_out_date, &reservation.guest_charge);
        printf("Reservation ID: %d\n", reservation.reservation_id);
        printf("Room Number: %d\n", reservation.room_number);
        printf("Check-In Date: %s\n", reservation.check_in_date);
        printf("Check-Out Date: %s\n", reservation.check_out_date);
        printf("Guest Charge: %.2lf\n", reservation.guest_charge);
        printf("----------------------------------------\n");
    }

    fclose(file);
}

// Function to cancel a reservation

void cancelReservation() {
    FILE *reservationsFile = fopen(RESERVATIONS_FILE, "r");
    FILE *tempFile = fopen("temp_reservations.txt", "w");
    FILE *roomsFile = fopen(ROOMS_FILE, "r+");
    if (reservationsFile == NULL || tempFile == NULL || roomsFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int reservation_id;
    printf("Enter Reservation ID to cancel: ");
    scanf("%d", &reservation_id);

    struct Reservation reservation;
    struct Room1 room;
    int reservation_found = 0;
    char line[256]; // Declare line buffer

    // Process reservations to find and remove the specified reservation
    while (fgets(line, sizeof(line), reservationsFile)) {
        sscanf(line, "%d,%d,%[^,],%[^,],%d,%[^,],%[^,],%lf", &reservation.reservation_id, &reservation.customer_id, reservation.reservation_status, reservation.guest_status, &reservation.room_number, reservation.check_in_date, reservation.check_out_date, &reservation.guest_charge);

        if (reservation.reservation_id == reservation_id) {
            reservation_found = 1;
            continue; // Skip writing this reservation to the temp file
        }

        fprintf(tempFile, "%d,%d,%s,%s,%d,%s,%s,%lf\n", reservation.reservation_id, reservation.customer_id, reservation.reservation_status, reservation.guest_status, reservation.room_number, reservation.check_in_date, reservation.check_out_date, reservation.guest_charge);
    }

    fclose(reservationsFile);
    fclose(tempFile);

    // Replace the old reservations file with the updated one
    remove(RESERVATIONS_FILE);
    rename("temp_reservations.txt", RESERVATIONS_FILE);

    if (reservation_found) {
        // Update room availability to "available"
        FILE *roomsTempFile = fopen("temp_rooms.txt", "w");
        if (roomsTempFile == NULL) {
            printf("Error opening file.\n");
            return;
        }

        while (fgets(line, sizeof(line), roomsFile)) {
            sscanf(line, "%d,%[^,],%[^,],%d,%lf", &room.room_number, room.room_status, room.availability, &room.room_capacity, &room.room_rate);

            if (reservation.room_number == room.room_number) {
                strcpy(room.availability, "available");
            }

            fprintf(roomsTempFile, "%d,%s,%s,%d,%lf\n", room.room_number, room.room_status, room.availability, room.room_capacity, room.room_rate);
        }

        fclose(roomsFile);
        fclose(roomsTempFile);

        // Replace the old rooms file with the updated one
        remove(ROOMS_FILE);
        rename("temp_rooms.txt", ROOMS_FILE);

        printf("Reservation canceled successfully.\n");
    } else {
        printf("Reservation ID not found.\n");
    }
}

///////////////////////////////////////////////////////////////////////////////////////////// <5. guest system> 
#define ROOMS_FILE "rooms.txt"

// Structure definitions
struct Room2 {
    int room_number;
    char room_status[20];
    char availability[20];
    int room_capacity;
    double room_rate;
};

// Function prototypes
void guestMenu();
void viewRoomAvailability();
void searchRoomDetails();

// Main function
// Function to display guest menu
void guestMenu() {
    int choice;
    do {
        printf("\nGuest Menu:\n");
        printf("1. View Room Availability\n");
        printf("2. Search Room Details and Rates\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                viewRoomAvailability();
                break;
            case 2:
                searchRoomDetails();
                break;
            case 3:
                printf("Exiting Guest menu.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    } while (choice != 3);
}

// Function to view room availability
void viewRoomAvailability() {
    FILE *file = fopen(ROOMS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", ROOMS_FILE);
        return;
    }

    printf("\nRoom Availability:\n");
    printf("----------------------------------------\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        struct Room2 room;
        int scanned = sscanf(line, "%d,%[^,],%[^,],%d,%lf", &room.room_number, room.room_status,
                             room.availability, &room.room_capacity, &room.room_rate);

        // Debug: Print the scanned values
        printf("Scanned values: %d\n", scanned);
        if (scanned != 5) {
            printf("Error parsing line: %s\n", line);
            continue;
        }

        // Convert the availability status to lowercase for comparison
        for (int i = 0; room.availability[i]; i++) {
            room.availability[i] = tolower((unsigned char)room.availability[i]);
        }

        if (strcmp(room.availability, "available") == 0) {
            printf("Room Number: %d\n", room.room_number);
            printf("Room Status: %s\n", room.room_status);
            printf("Room Capacity: %d\n", room.room_capacity);
            printf("Room Rate: %.2lf\n", room.room_rate);
            printf("----------------------------------------\n");
        }
    }
    fclose(file);
}

// Function to search room details and rates
void searchRoomDetails() {
    int room_number;
    printf("Enter room number to search: ");
    scanf("%d", &room_number);

    FILE *file = fopen(ROOMS_FILE, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", ROOMS_FILE);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        struct Room2 room;
        int scanned = sscanf(line, "%d,%[^,],%[^,],%d,%lf", &room.room_number, room.room_status,
                             room.availability, &room.room_capacity, &room.room_rate);

        // Debug: Print the scanned values
        printf("Scanned values: %d\n", scanned);
        if (scanned != 5) {
            printf("Error parsing line: %s\n", line);
            continue;
        }

        if (room.room_number == room_number) {
            found = 1;
            printf("\nRoom Details:\n");
            printf("----------------------------------------\n");
            printf("Room Number: %d\n", room.room_number);
            printf("Room Status: %s\n", room.room_status);
            printf("Room Availability: %s\n", room.availability);
            printf("Room Capacity: %d\n", room.room_capacity);
            printf("Room Rate: %.2lf\n", room.room_rate);
            printf("----------------------------------------\n");
            break;
        }
    }
    if (!found) {
        printf("Room number %d not found.\n", room_number);
    }
    fclose(file);
}