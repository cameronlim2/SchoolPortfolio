var scanner = function()
{

    var inputString = document.getElementById("input");
    var outputString = document.getElementById("output");
    var myValue = inputString.value;
    myValue = myValue.trim();
    var token = myValue.split("");
    Expr(token);

    if (token[0] != "$" || token[1] != null)
        return error();
};

// Setting up tokens

var Digit = function(token)
{
    if (token[0] === '0')
        token = compare("0", token);
    else if (token[0] === '1')
        token = compare('1', token);
    else if (token[0] === '2')
        token = compare('2', token);
       else if (token[0] === '3')
        token = compare('3', token);
    else
        error();
}

var Factor = function(token)
{
    if (token[0] === '(')
    {
        token = compare("(", token);
        Expr(token);
        token = compare(")", token);
    }
    else
        Digit(token);
};

var Term = function(token)
{
    Factor(token);
    while((token[0] === '*') || (token[0] === '/'))
    {
        if (token[0] === '*')
        {
            token = compare('*', token);
            Factor(token);
        }
        else if (token[0] === '/')
        {
            token = compare('/', token);
            Factor(token);
        }
    }
};

var Expr = function(token)
{
    Term(token);
    while((token[0] === '+') || token[0] === '-')
    {
        if (token[0] === '+')
        {
            token = compare("+", token);
            Term(token);
        }
        else if (token[0] === '-')
        {
            token = compare("-", token);
            Term(token);
        }
    }
};

// comparison handling

var compare = function(x, tk)
{
    if (tk[0] === x)
    {
        tk.shift();
        if (tk[0] == "$") return valid();
        return tk;
    }
    error();
}

// Error handling

var error = function()
{
    var input = document.getElementById("input").value;
    var output = document.getElementById("output");
    var value = input.value;
    output.innerHTML = "Invalid : " + input;
}

// Run it

var valid = function()
{
    var input = document.getElementById("input").value;
    var output = document.getElementById("output");
    var value = input.value;
    output.innerHTML = "Valid: " + input;
};

