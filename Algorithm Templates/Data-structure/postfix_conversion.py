def precedance_order(sym):
    precedance = {
        '^': 5,
        '/': 4,
        '*': 3,
        '+': 2,
        '-': 2
    }
    return precedance[sym]

def postfix_conversion(_list):
    _stack = []
    _string = ""
    for i in range(0, len(_list)):
        print(_stack, _string)
        if '0' <= _list[i] <= '9':
            _string = _string + " " + _list[i]
        else:
            if len(_stack) == 0:
                _stack.append(_list[i])
            else:
                while len(_stack) > 0 :
                    if precedance_order(_stack[-1]) > precedance_order(_list[i]):
                        _string = _string + " " + _stack[-1]
                        del _stack[-1]
                    elif precedance_order(_stack[-1]) < precedance_order(_list[i]):
                        break
                    else:  # equal precedence
                        if _stack[-1] in ['^']: # right associative
                            break
                        elif _stack[-1] in ['+', '-', '*', '/']: # left associative
                            _string = _string + " " + _stack[-1]
                            del _stack[-1]
                _stack.append(_list[i])
    while len(_stack) > 0:
        _string = _string + " " + _stack[-1]
        del _stack[-1]
    print(_string)
    return _string.strip().split(' ')


def postfix_evaluation(_string):
    _stack = []
    for i in range(0, len(_string)):
        print(_stack, _string[i])
        try:
            val = int(_string[i])
            _stack.append(val)
        except Exception as e:
            if len(_stack) >= 2:
                v1 = _stack.pop()
                v2 = _stack.pop()
                if _string[i] == '+':
                    _stack.append(v1+v2)
                if _string[i] == '-':
                    _stack.append(v2-v1)
                if _string[i] == '*':
                    _stack.append(v2*v1)
                if _string[i] == '/':
                    _stack.append(v2//v1)
                if _string[i] == '^':
                    res = 1
                    for j in range(0, v1):
                        res *= v2
                    _stack.append(res)
            elif len(_stack) == 1:
                v1 = _stack.pop()
                if _string[i] == '-':
                    _stack.append(-v1)
    print(_stack)


exp = postfix_conversion(['3', '^', '7', '-', '5', '/', '7', '+', '3', '*', '4', '/', '5', '+', '6', '*', '2'])
postfix_evaluation(exp)


