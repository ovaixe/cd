OPERATORS = set(['+', '-', '*', '/', '(', ')'])

# INP z = -a * b + c

PRI = {'+':1, '-':1, '*':2, '/':2}
### INFIX ===> POSTFIX ###
def infix_to_postfix(formula):
    stack = [] # only pop when the coming op has priority 
    output = ''
    for ch in formula:
        #print(stack)
        #print(ch)
        if ch not in OPERATORS:
            output += ch
        elif ch == '(':
            stack.append('(')
        elif ch == ')':
            while stack and stack[-1] != '(':
                output += stack.pop()
            stack.pop() # pop '('
        else: 
            while stack and stack[-1] != '(' and PRI[ch] <= PRI[stack[-1]]:
                output += stack.pop()
            stack.append(ch)
    # leftover
    while stack: 
        output += stack.pop()
    print(f'POSTFIX: {output}')
    return output
### THREE ADDRESS CODE GENERATION ###
def generate3AC(pos):
    print("### THREE ADDRESS CODE GENERATION ###")
    exp_stack = []
    t = 1
    for i in pos:
        if i not in OPERATORS:
            exp_stack.append(i)
        else:
            if exp_stack[-2]=='=':
                first =''
            else: first = exp_stack[-2]
            print(f't{t} := {first} {i} {exp_stack[-1]}')
            exp_stack=exp_stack[:-2]
            exp_stack.append(f't{t}')
            t+=1            
    if len(exp_stack) == 2:
        print(exp_stack[0],"=",exp_stack[1])
    elif len(exp_stack) == 3:
        print(exp_stack[0],exp_stack[1],exp_stack[2])
expres = input("INPUT THE EXPRESSION: ")
pos = infix_to_postfix(expres)
generate3AC(pos)
