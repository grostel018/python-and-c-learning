def get_input():
    """Get a valid number input from user"""
    while True:
        try:
            user_input = input("\nEnter an operand: ")
            return float(user_input)
        except ValueError:
            print("\nEnter a valid number!")

def addition(a, b):
    return a + b

def subtraction(a, b):
    return a - b

def multiplication(a, b):
    return a * b

def division(a, b):
    """Division with zero division check"""
    if b == 0:
        print("Error: Division by zero!")
        return 0.0
    return a / b

def get_operator():
    """Get a valid operator from user"""
    valid_operators = ['+', '-', '*', '/']
    
    print("\nEnter the operator")
    print("\nSelect between (+, -, * or /)")
    
    while True:
        op = input().strip()
        if op in valid_operators:
            return op
        else:
            print("\nEnter a valid operator:")

def calculate(num1, num2):
    """Perform calculation based on operator"""
    operator = get_operator()
    
    print("=================")
    
    result = 0
    if operator == '+':
        result = addition(num1, num2)
    elif operator == '-':
        result = subtraction(num1, num2)
    elif operator == '*':
        result = multiplication(num1, num2)
    elif operator == '/':
        result = division(num1, num2)
    
    print(f"\nThe result of {num1} {operator} {num2} is: {result}")
    return result

def new_calc():
    """Perform a new calculation"""
    num1 = get_input()
    print("=================")
    num2 = get_input()
    print("=================")
    calculate(num1, num2)

def main():
    """Main program loop"""
    print("\t-----Welcome to the calculator app-----\t")
    print("\t           =================")
    
    choice = 'y'
    
    while choice.lower() == 'y':
        print("\nNew calculation:\n")
        new_calc()
        
        choice = input("\nDo you wish to make another calculation? (y/n): ")
        print("\t           =================")
    
    print("\nGoodbye!")

if __name__ == "__main__":
    main()
