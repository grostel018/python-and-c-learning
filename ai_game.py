import random

# Use descriptive names for constants
CHOICES = {
    1: "paper",
    2: "scissors",  # Fixed spelling: "scisors" → "scissors"
    3: "rock"
}

# Game rules matrix - more maintainable than multiple if/elif statements
RULES = {
    (1, 2): "scissors cut paper, you lost!",
    (2, 1): "scissors cut paper, you won!",
    (3, 1): "paper covers rock, you lost!",
    (1, 3): "paper covers rock, you won!",
    (2, 3): "rock breaks scissors, you lost!",
    (3, 2): "rock breaks scissors, you won!"
}

def get_user_choice():
    """Get and validate user input."""
    while True:
        try:
            choice = int(input("Choose: 1 for paper, 2 for scissors, 3 for rock: "))
            if choice in CHOICES:
                return choice
            else:
                print("Please enter a number between 1 and 3.")
        except ValueError:
            print("Please enter a valid number.")

def get_play_again():
    """Ask if user wants to play again."""
    while True:
        try:
            response = input("\nPlay again? (yes/no): ").lower().strip()
            if response in ['y', 'yes', '1']:
                return True
            elif response in ['n', 'no', '2']:
                return False
            else:
                print("Please enter 'yes' or 'no'.")
        except:
            print("Invalid input.")

def main():
    print("Welcome to Rock, Paper, Scissors!")
    
    while True:
        user_choice = get_user_choice()
        ai_choice = random.choice(list(CHOICES.keys()))
        
        print(f"\nYou chose: {CHOICES[user_choice]}")
        print(f"AI chose: {CHOICES[ai_choice]}")
        
        # Check for tie first
        if user_choice == ai_choice:
            print("It's a tie!")
        else:
            # Look up result in rules dictionary
            result = RULES.get((user_choice, ai_choice))
            if result:
                print(result)
            else:
                # If not found, it means the user won (since we covered all AI win scenarios)
                # Look for the reverse scenario
                reverse_result = RULES.get((ai_choice, user_choice))
                if reverse_result:
                    # Swap "you won!" and "you lost!" from the AI's perspective
                    result_text = reverse_result.replace("you won!", "you lost!").replace("you lost!", "you won!")
                    print(result_text)
        
        if not get_play_again():
            print("\nThanks for playing! Goodbye!")
            break

if __name__ == "__main__":
    main()
