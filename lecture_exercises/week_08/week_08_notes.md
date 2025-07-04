

# HTML
https://validator.w3.org/#validate_by_input

### tags:
<html>, <head>, <title>, <body>, ...
#####text tags:
<b>, <i>, <u>, ...

#####paragraph, header
<p>, <h1> <h6>, ...

##### lists:
<ol>
    <il>xxx</il>
    <il>xxx</il>
    <il>...</il>
</ol>
<uo>
    <il>xxx</il>
    <il>xxx</il>
    <il>...</il>
</ul>

##### tables
<table>
    <tr>
        <td>aaa</td> <!--table data-->
        <td>bbb</td>
        <td>ccc</td>
    </tr>
    <tr>
        <td>ddd</td>
        <td>eee</td>
        <td>fff</td>
    </tr>
</table>

#### forms
<div>
    <form>
        Text: <input name="a" type="text" />  <!--this is called a self-closing tag: it doesn't need a closing tag.-->
        Password: <input name="b" type="password" />
        Radio: <input name="c" type="radio" />
        Checkbox: <input name="d" type="checkbox" />
        Submit: <input name="e" type="submit" />
    </form>
</div>


#### other tags
<a href=X>, </a> Creates a hyperlink to web page X
<img src=X ... /> Another self-closing tag for displaying an image located at X,
<!DOCTYPE html> Specific to HTML5, lets the browser know that’s the standard you’re using.
<!--, --> Demarcate the beginning and end of an HTML comment


# CSS
First we identify a selector, then between curly braces we establish the style in key/value pairs.

Tag example:
body
    {
        background-colot: blue;
    }

Common CSS properties:
border
background-color
color
font-size
font-family
text-align

We can also select by ID or class:
class example:
.students
    {
        background-color: yellow;
        opacity: 0.34;
    }

ID example:
#unique
    {
        font-family: times;
        folor: red;
    }
Naming tags in html happens inside the triangle brackets: <... id="unique"...>

#### comments:
/* lksgksdgjdo */


### css file
We can define all the styles in a separated file called xxx.css and refering to it in the html file:
<html>
    <link href="path/to/css/file.css" rel="stylesheet" />



# JavaScript
We can write javascript in a separate file ended with .js.
We then can source the file in the <script> tag of the html and using its "src" attribute.

#### variable
var x = 44;

#### conditionals
if
else if
else
switch
?:

#### loops
while
do-while
for

To iterate through all key / value pairs of an object:
for (var key in object)
    {
        // Use object[key] here
    }
or:
for (var key of object)
    {
        // Use key here
    }

#### functions
function functioname
    {

    }
They can be anonymous, do not necessarily need a name.

#### arrays
They are objects that have a few properties:
    - array.size
    - .pop()
    - .push()
    - .shift()
    = .map() used to apply a function to all elements in the array with an anonimus fucntion
var nums = [1, 2, 3, 4, 5];
var mixed = [1, "foo", 4.66, true, false];

map example with anonimous function:
var nums = [1, 2, 3, 4, 5]
nums = nums.map(function(num) {
    return num * 2;
});

#### objects
they look very similar to python dicts:
var objectname: {year: 1946, model: 'Beetle', color: red}


#### concatenating info
var wkArray = [
    'Monday',
    'Tuesday',
    'Wednesday',
    'T',
    'F',
    'S',
    'S',
]
console.log(wkArray[day] + 'is day number '
    + (pareseInt(day) + 1) + ' of the week.';)


#### events
Goes hand in hand with html and is when something happens: button click, page closed, hover, ...
In html many elements support events.
We can pass 'event' as an arg to the  fucntion called. This var has all info of the event
function alertName(event)
    {
        var trigger = event.srcElement;
        alert('You clicked on ' + trigger.innerHTML);
    }


# DOM
The Document Object Model.
Objects contain properties and methods.
Contains the structure of the entire web page
Some properties:
    - innerHTML
    - nodedame
    - id
    - parentNode
    - childNodes
    - attributes
    - style
Some methods:
    - getElementById(id)
    - getElementsByTagName(tag)
    - appendChiild(node)
    - removeChild(node)

## jQuery
http://api.jquery.com
Library that helps manipulate the DOM with less typing.
Example without jQuery:
document.getElementById('colorDiv').style.backgroundColor = 'green
With jQuery:
$('#colorDiv'.css('backgroundColor', 'green'))
