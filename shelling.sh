
#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo "=========================="
    echo "      STUDENT ADDRESS BOOK"
    echo "=========================="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo "=========================="

    read -p "Enter your choice: " choice

    case $choice in

    1)
        touch "$FILE"
        echo "Address Book Created Successfully."
        ;;

    2)
        if [ -f "$FILE" ]
        then
            if [ -s "$FILE" ]
            then
                echo "Address Book Records:"
                cat "$FILE"
            else
                echo "Address Book is Empty."
            fi
        else
            echo "Address Book Does Not Exist."
        fi
        ;;

    3)
        read -p "Enter Roll No: " id
        read -p "Enter Student Name: " name
        read -p "Enter Phone: " phone
        read -p "Enter City: " city

        echo "$id | $name | $phone | $city" >> "$FILE"

        echo "Record Inserted Successfully."
        ;;

    4)
        if [ -f "$FILE" ]
        then
            read -p "Enter Roll No to Delete: " id

            if grep -q "^$id |" "$FILE"
            then
                grep -v "^$id |" "$FILE" > temp.txt
                mv temp.txt "$FILE"
                echo "Record Deleted Successfully."
            else
                echo "Record Not Found."
            fi
        else
            echo "Address Book Does Not Exist."
        fi
        ;;

    5)
        if [ -f "$FILE" ]
        then
            read -p "Enter Roll No to Modify: " id

            if grep -q "^$id |" "$FILE"
            then
                read -p "Enter New Name: " name
                read -p "Enter New Phone: " phone
                read -p "Enter New City: " city

                sed -i "s/^$id |.*/$id | $name | $phone | $city/" "$FILE"

                echo "Record Modified Successfully."
            else
                echo "Record Not Found."
            fi
        else
            echo "Address Book Does Not Exist."
        fi
        ;;

    6)
        echo "Exiting Address Book..."
        exit
        ;;

    *)
        echo "Invalid Choice."
        ;;

    esac

    echo
done
