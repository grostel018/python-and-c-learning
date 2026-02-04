import random

list1 = [1, 2, 3]






wantplay = 1

while (wantplay == 1) :
    
    choix = int (input("choose between 1- for paper, 2- for scisors, 3- for rock \n"))

    ai = random.choice(list1)

    print (f"the ai choosed {ai} \n")

    if (choix == 1 and ai == 2) :
        print("scissors cut the paper, you lost")
    elif (choix == 2 and ai == 1) :
        print("You won, scissors cut the paper")
    elif (choix == 3 and ai == 1) :
        print("You lost, paper eat the rock")
    elif (choix == 1 and ai == 3) :
        print("You won, paper eat the rock")
    elif (choix == 2 and ai == 3) :
        print("You lost, rock break the scissors")
    else :
        print("You won, rock break the scissors")

    wantplay = int(input(" \n Do you wanna again ? 1- for yes, 2- for no "))
    
    