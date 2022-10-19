#Corner Grocer
#Steven Anderson


import re
from sre_constants import CATEGORY_UNI_NOT_SPACE
import string

#PrintFrequency which opens the List.txt file and prints the data 
def PrintFrequency():
    frequency = {}
    text_file = open("List.txt", "r")
    #Lowercase the file data
    file_string = text_file.read().lower()
    #setting parameters for the string that avoid numbers and words less that 3 characters or more than 25
    string_parameters = re.findall(r'\b[a-z]{2,25}\b', file_string)

    #runs the for loop as long as there is another word in the string
    for word in string_parameters:
        count = frequency.get(word,0)
        #increase the count by one for the word
        frequency[word] = count + 1 
    #.keys used to get all elements
    frequency_list = frequency.keys()

    print("%-*s %s" %(20,"Item", "Frequency"))
    print("--------------------------------------")
    #prints the words and frequency of those words in a formated list
    for words in frequency_list:
        print ("%-*s %s" %(20, words, frequency[words]))
    print("--------------------------------------")

#function for taking in a word and printing frequency of that word
def PrintOneItemFrequency(v):
    frequency = {}
    #open, read, lowercase, then set perameters for the string the file is assigned to
    text_file = open("List.txt", "r")
    file_string = text_file.read().lower()
    string_parameters = re.findall(r'\b[a-z]{3,25}\b', file_string)
    #set userWord lowercase to avoid word not being recognized
    userWord = v.lower()

    #for loop used to count how many times the word repeats in the file incremeting by +1 when found
    for word in string_parameters:
        if (word == userWord):
            count = frequency.get(word,1)
            frequency[word] = count + 1
    #return the count of the frequency of the user inputed item
    return count

#WriteToFileFrequency used to open file and write to another
def WriteToFileFrequency():
    frequency = {}
    #open, read, lowercase, then set perameters for the string that the file is copied to
    text_file = open("List.txt", "r")
    #open the frequency.dat file
    dat_file = open("frequency.dat", "w")
    file_string = text_file.read().lower()
    string_parameters = re.findall(r'\b[a-z]{3,25}\b', file_string)

    #for loop used to find and assign the frequency for each item
    for word in string_parameters:
        count = frequency.get(word,0)
        frequency[word] = count + 1     
    frequency_list = frequency.keys()

    #for loop used to assign the frequency_list which includes the item and frequencies to the frequency.dat file
    for words in frequency_list:
        dat_file.write('%s %d\n' %(words,frequency[words]))
