#!/bin/bash

# File to store address book entries
ADDRESS_BOOK="address_book.txt"

# Function to add an entry
add_entry() {
    echo "Enter Name:"
    read name
    echo "Enter Phone Number:"
    read phone
    echo "Enter Email:"
    read email

    echo "$name, $phone, $email" >> $ADDRESS_BOOK
    echo "Entry added successfully!"
}

# Function to view all entries
view_entries() {
    if [ -s $ADDRESS_BOOK ]; then
        echo "Address Book Entries:"
        cat $ADDRESS_BOOK
    else
        echo "No entries found."
    fi
}

# Function to search for an entry by name
search_entry() {
    echo "Enter Name to Search:"
    read name
    grep -i "$name" $ADDRESS_BOOK
    if [ $? -ne 0 ]; then
        echo "No entry found for $name."
    fi
}

# Function to delete an entry by name
delete_entry() {
    echo "Enter Name to Delete:"
    read name
    grep -i -v "$name" $ADDRESS_BOOK > temp.txt
    mv temp.txt $ADDRESS_BOOK
    echo "Entry deleted successfully!"
}

# Main menu
while true; do
    echo "Address Book Menu"
    echo "1. Add Entry"
    echo "2. View Entries"
    echo "3. Search Entry"
    echo "4. Delete Entry"
    echo "5. Exit"
    echo "Enter your choice:"
    read choice

    case $choice in
        1)
            add_entry
            ;;
        2)
            view_entries
            ;;
        3)
            search_entry
            ;;
        4)
            delete_entry
            ;;
        5)
            exit 0
            ;;
        *)
            echo "Invalid choice. Please try again."
            ;;
    esac
done
