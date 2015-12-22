JavaScript Animation library	{#JavaScriptAnimLib}
==========

Intro {#IntroJavaScriptAnimLib}
==========

We've been thinking about how to help developers using Coherent UI create better
animations easier and this inspired us to make an animation library with a simple
API. We are decided to use a JS-based design instead of a CSS3-based, because JS
allows easier control on what is going on.
After deep research we chose GSAP animation to be the core of our
framework. Before choosing GSAP we experimented with 4 JS libraries:
web-animations, web-animations-next, GSAP, jQuery. All libraries have roughly
the same features. We compared their performance and stability.
GSAP claims to be the fastest JS animation library and from our experiments we
can confirm that – at least compared to the other 3 libraries. It is also very
well documented and has all animation features imaginable.
For full list of documentation and tutorials of GSAP, you can read at
[https://greensock.com/gsap](https://greensock.com/gsap)

Coherent animation library
--------------------

Coherent animation library is based on the GSAP animation library.
We’ll also provide direct access to GSAP without trying to hide anything.
The features-list of GSAP is very long and we want our users to be able to
use anything they might need. And for that reason, we made syntax closer to
the way animations are declared in CSS3 and expanded the methods of GSAP
to facilitate the making of animation.

Sample usage {#SimpleJavaScriptAnimLib}
==========

In this example we will show you how to create a very simple animation. The
animation will represent a moving div element, which will come from left to the
current css definition of it.

1. Include the files
--------------------
First of all you have to include several scripts files in your HTML page in 
following the order:

~~~~~~~~~~~~~~~~~~~~~{.js}
<script src="./js/gsap/TweenMax.js"></script>
<script src="./js/gsap/TimelineMax.js"></script>
<script src="./js/coherent_animations.js"></script>
~~~~~~~~~~~~~~~~~~~~~

Now let's define the css properties of the element.

~~~~~~~~~~~~~~~~~~~~~{.js}
#rect {
position: absolute;
  top: 50px;
  left: 250px;
  width: 200px;
  height: 200px;
  background: #000;
}
~~~~~~~~~~~~~~~~~~~~~

This will create a black rectangle, placed at an absolute position
against the page body tag. Current left position it's 250px and top is 50px.
Our idea is to show how easily to animate movement of this rectangle,
starting from `left:0`, going to the current `250px` and then from `top:0` move
to `top: 50px`.

2. Define the animation
--------------------
The animation definition is an array of objects:

~~~~~~~~~~~~~~~~~~~~~{.js}
var moveRect = [
  {percent: 0.5, left:0},
  {percent: 1, top: 0}
]
~~~~~~~~~~~~~~~~~~~~~

Each object acts like a keyframe - the `percent` property corresponds to the time
at which this keyframe is to be played and the other properties provided describe
the frame itself. 

3. Create the animation/timeline
--------------------
The next step is to create a new `CoherentAnimation` object.

~~~~~~~~~~~~~~~~~~~~~{.js}
var anim = new CoherentAnimation();
~~~~~~~~~~~~~~~~~~~~~

4. Play the animation
--------------------
Finally, we tie the animation and the div together and play the animation:

~~~~~~~~~~~~~~~~~~~~~{.js}
anim.caFrom({
  selector: '#rect',
  anims: moveRect,
  seconds: 2
}).play()
~~~~~~~~~~~~~~~~~~~~~

The `caFrom` method takes an object with the following properties as an argument:
* selector: select our element by id
* anims: the array of keyframes we defined above
* seconds: the duration of the animation in seconds. This property is required
if our key frames are percent-based. See below for an alternative.

Let us continue with an in-depth look of the library.

Animation definition {#AnimDefineJavaScriptAnimLib}
======
There are two ways to define animation properties - percent-based and seconds-based.

1. Percent based {#PercentJavaScriptAnimLib}
--------------------
~~~~~~~~~~{.js}
var moveDown = [
   {percent: 0.5, bottom: 10},
   {percent: 1, bottom: 20}
]
~~~~~~~~~~

This percent is based on the time in seconds **provided when calling `caFrom`**
as you already saw above. Must be an array of objects.

2. Seconds based {#SecondsJavaScriptAnimLib}
--------------------
The option lets you specify the time of the key frame in seconds. You can pass
an array with objects or a single object:

1. Array of objects
~~~~~~~~~~{.js}
var moveDown = [
  {seconds: 1, bottom: 10},
  {seconds: 2, bottom: 20}
];
~~~~~~~~~~

2. Single object
~~~~~~~~~~{.js}
var moveDown = {seconds: 1, bottom: 10};
~~~~~~~~~~

If you use an array of objects, animation will proceed in the order of elements
in the array - the rectangle will firstly move 10 pixels down, then another 10
pixels down.

Timeline object parameters: {#newCAObjectJavaScriptAnimLib}
==========
A `CoherentAnimation` can be configured with several options:

~~~~~~~~~~{.js}
new CoherentAnimation({repeat: 1, onRepeat: repeatHandler, yoyo: true});
~~~~~~~~~~

* repeat : Number - the umber of times that the animation should repeat after
its first iteration. If repeat is 1, the animation will play twice (the initial
play plus 1 repeat). Use -1 for an endless animation. This value must always be
an integer.

* onRepeat : Function - A function that will be called each time the
animation repeats.

* yoyo: Boolean - If true, every other repeat cycle will run in the opposite
direction so that the tween appears to go back and forth
(forward then backward). This has no affect on the `repeat` property though.
So if repeat is 2 and yoyo is false, the animation order will be:

`start - 1 - 2 - 3 - 1 - 2 - 3 - 1 - 2 - 3 - end`

But if yoyo is true, it goes like:

`start - 1 - 2 - 3 - 3 - 2 - 1 - 1 - 2 - 3 - end`

You can see full list of parameters on
[GSAP/TimelineMax](http://greensock.com/docs/#/HTML5/GSAP/TimelineMax/TimelineMax/)

Methods {#MethodsJavaScriptAnimLib}
==========

* **caTo(params)**: Adds a tween animation that starts with the object's current
style towards and animates it until the style defined in the animation is
achieved.<br>
  *params*: {Object} obj - this object must have a following parameters:
  * selector: {Object} DOM element object or javascript object.
  * anims: {(Object| Array)} a key frame or an array of key frames.
  * offset(optional): {Number} (default = +=0) — Controls the placement
   of the tween on the timeline (by default, it's the end of the timeline,
   like "+=0"). Use a number to indicate an absolute time in terms of
   seconds (or frames for frames-based timelines), or you can use a string
   with a "+=" or "-=" prefix to offset the insertion point relative to
   the **END** of the timeline. For example, "+=2" would place the tween 2
   seconds after the end, leaving a 2 second gap. "-=2" would create a 2-second
   overlap
  * seconds(optional): {Number} if you are using percents in your
  animation definition, you have to set the duration in seconds. Otherwise, this
  can be omitted.
<br><br>
* **caFrom()**: Adds a tween animation - that starts with the style defined in
the animation and animates it until the object's current style is achieved.<br>
*Parameters*: {Object} obj - takes the same parameters like `caTo()` method.
<br><br>
* **caStaggerTo()**: Tweens an array of targets to a common set of destination
values, but staggers their start times by a specified amount of time, creating
an evenly-spaced sequence.<br>
  *Parameters*: {Object} obj - this object must have a following parameters:
  * selector: DOM elements('.myClass') or
  javascript array([element1, element2, element3])
  * anims: {Object} this is your snippet animations object
  * stagger: {Number} - Amount of time in seconds (or frames if the timeline
  is frames-based) to stagger the start time of each tween.
  * offset(optional): {Number} (default = +=0) — same like offset parameters
  of caTo() method.
  * seconds(optional): {Number} if you are using a percent in your snippet of
  animation definition, you have to set duration time in seconds.
<br><br>
* **caStaggerFrom()**: The animation will start from your snippet definition
to the reach of the current values of the animated object. <br>
*Parameters*: {Object} obj - takes the same parameters like `caStaggerTo()`
method.

You can see full list of methods on
[GSAP/TimelineMax](http://greensock.com/docs/#/HTML5/GSAP/TimelineMax/)

Advance animations {#AdvanceJavaScriptAnimLib}
======

Menu animation example
--------------------

In this example every menu button will enter the page from a different position.

--------------------
~~~~~~~~~~~~~~~{.html}
<!-- Start Menu -->
<nav class="menu" id="menu-start">
  <ul>
    <li>
      <button type="button" id="start-btn" class="btn btn-default">
      Start
      </button>
    </li>
    <li>
      <button type="button" id="options-btn" class="btn btn-default">
      Options
      </button>
    </li>
    <li>
      <button type="button" id="credits-btn" class="btn btn-default">
      Credits
      </button>
    </li>
    <li>
      <button type="button" id="quit-btn" class="btn btn-default">
      Quit
      </button>
    </li>
  </ul>
</nav>
~~~~~~~~~~~~~~~

Style our menu:
--------------------
~~~~~~~~~~{.css}
.menu {
  position: absolute;
  top: 120px;
  width: 250px;
  left: 0;
  right: 0;
  margin-left: auto;
  margin-right: auto;
}
.menu ul {
  position: relative;
  padding: 10px;
}
.menu ul li {
  position: relative;
  margin: 2px 0;
  height: 45px;
}
.menu ul button {
  position: absolute;
  top: 0;
}
~~~~~~~~~~

Now with this styling rules we set the menu's position in the center of the page
and add four buttons to it. Let's create an animation for each button.

--------------------
~~~~~~~~~~{.js}
var moveFromLeft = {seconds: 1, left: -450, opacity: 0, ease: Circ.easeIn},
moveFromRight = {seconds: 1, right: -450, opacity: 0, ease: Circ.easeIn},
moveFromTop = {seconds: 1, top: -400, opacity: 0, ease: Circ.easeIn},
moveFromDown = {seconds: 1, top: 'auto', bottom: -300, opacity: 0, ease: Circ.easeIn};
~~~~~~~~~~

We already saw what most of the code above does. The only exception is the `ease`
parameter - easing allows you to change the speed of your animation over time.

You can see full list of easing effects on
[GSAP/easing](http://greensock.com/jump-start-js#easing) -
_By default easing effect is linear_

Next, create a `new CoherentAnimation` and call `caFrom`. By default
`CoherentAnimation` it's always pauses and we need to call `play()` to start it.

~~~~~~~~~~{.js}
var coherentMenu = new CoherentAnimation();

coherentMenu.caFrom({
    selector: "#start-btn",
    anims: moveFromTop
  }).caFrom({
    selector: "#options-btn",
    anims: moveFromLeft,
  offset: "-=1"
  }).caFrom({
    selector: "#credits-btn",
    anims: moveFromRight,
    offset: "-=1"
  }).caFrom({
    selector: "#quit-btn",
    anims: moveFromDown,
    offset: "-=1"
}).play();
~~~~~~~~~~

Here's the result:
![img def](menu-screen1.jpg)

Create a blink effect by clicking on the buttons
--------------------

To create a blink effect on our buttons we can use this snippet:

~~~~~~~~~~{.js}
// Array with objects definition for animations
var blink = [
  {percent: 0.2, opacity: 0},
  {percent: 0.4, opacity: 1},
  {percent: 0.7, opacity: 0},
  {percent: 1, opacity: 1}
];
~~~~~~~~~~

Now with jQuery we can attach a click event on every button in the menu.

~~~~~~~~~~{.js}
$('.menu .btn').on('click', function() {
    var blinkBtn = new CoherentAnimation();
    blinkBtn.caTo({
    selector: $(this),
    anims: blink,
    seconds: 0.3
  }).play();
});
~~~~~~~~~~
![img def](menu-screen2.jpg)

Using with requirejs {#ScriptsJavaScriptAnimLibRequirejs}
==========
To use Coherent Animation with requirejs you have to check the paths in
`coherent_animation.js` file.

~~~~~~~~~~{.js}
require.config({
  // By default coherent_animations.js is in the directory
  // js/libs/coherent_animation/coherent_animations.js starting
  // from your index.html file. If you change the path you need
  // to change the paths on TimelineMax and TweenMax below.
  paths: {
  TimelineMax: '../../../js/gsap/TimelineMax',
  TweenMax: '../../../js/gsap/TweenMax',
  },
  shim: {
  'TimelineMax': ['TweenMax'],
  }
}
~~~~~~~~~~

Now in `main.js` just include the `coherent_animation.js` file in require.config and use it.

~~~~~~~~~~{.js}
require.config({
  paths: {
  CoherentAnimation:'../../../js/coherent_animations'
  },
}

// Correct order to load css files
require(['CoherentAnimation'], function(CoherentAnimation) {
  // your code starts here

});
~~~~~~~~~~

\tableofcontents
