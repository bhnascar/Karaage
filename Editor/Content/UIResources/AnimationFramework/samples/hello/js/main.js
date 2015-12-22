window.addEventListener('load', function() {

  // Object definitions for animations
  // Properties of object:
  // duration: How long in seconds will be the animation
  // left: move div element to -250px left or start from -250px left.
  // top: move element from or to 50px top position.
  // ease: easing allows you to change the speed of your animation over time.
  // You can see full list of easing effects on http://greensock.com/jump-start-js#easing
  // By default easing effect is linear
  // offset "-=1" property of last object means that rotation will start 1 second back in time. That means the previous animation to move left by 150px and rotation will be animated together.

  var movementDuration = [
    {seconds: 1, top: 50, ease:Back.easeIn},
    {seconds: 1, left: 250},
    {seconds: 1, top: 150, ease: Bounce.easeOut},
    {seconds: 1, left: 150},
    {seconds: 1, rotationY: 360, offset: '-=1'}
  ];

  // Create a new coherent animation object and repeat animation five times
  // For full rules of properties take look on http://greensock.com/docs/#/HTML5/GSAP/TimelineMax/TimelineMax/
  var logoAmin = new CoherentAnimation({repeat: 5});

  // caTo will run the animation from current object or DOM element values to the reach the sended values of animations. The method take object as argument whit properties:
  // selector: DOM element or object
  // anims: object or array of object to run animation
  logoAmin.caTo({
    selector: '#logo-duration',
    anims: movementDuration
  }).play();
}, false);
