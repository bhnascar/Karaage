window.addEventListener('load', function() {

  // Object definitions for animations
  // Properties of object:
  // duration: How long in seconds will be the animation
  // width: set width of element
  // height: set height of element
  // ease: easing allows you to change the speed of your animation over time.
  // You can see full list of easing effects on http://greensock.com/jump-start-js#easing
  // By default easing effect is linear
  var circleAnim = [
    {seconds: 1, width: 0, height: 0, ease:Back.easeInOut},
    {seconds: 1, top: 250, ease: Bounce.easeOut}
  ];

  // Add event listener on button
  document.getElementById('hit-btn').addEventListener('click', function() {
    // Create a new DOM element with class ball
    var ballElement = document.createElement('span');
    var left = getRandomArbitrary(0, 300);
    ballElement.className = 'ball';
    ballElement.style.left = left;

    var cont = document.getElementById('scene');
    // Append .ball to #scene
    cont.appendChild(ballElement);

    // Create a new coherent animation object
    var ballHitAnim = new CoherentAnimation();

    // Now with chain methods play animation. First play circleAnim - next play fade in animation by waiting 2 seconds. Finaly run callback function after six seconds from start the animation.
    // If you want to add callback function directly after end of fade in animation, you can do this by set onComplete property in anims object who has sending. For example - anims: {duration: 0.5, opacity: 0, delay: 2, onComplete: function() { removeElement(ballElement); }}
    ballHitAnim.caTo({
      selector: ballElement,
      anims: circleAnim
    }).caTo({
      selector: ballElement,
      anims: {seconds: 0.5, opacity: 0, delay: 2}
    }).addCallback(removeElement, 6, [ballElement]).play();
  }, false);

  function removeElement(elem) {
    document.getElementById('scene').removeChild(elem);
  }

  function getRandomArbitrary(min, max) {
    return Math.random() * (max - min) + min;
  }
}, false);
