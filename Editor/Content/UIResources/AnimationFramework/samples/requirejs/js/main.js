(function() {
  require.config({
    paths: {
      jquery: '../../components/jquery/jquery-1.11.1.min',
      CoherentAnimation:'../../../js/coherent_animations',
    },
  });

  require(['jquery', 'CoherentAnimation'], function($, CoherentAnimation) {

    // Create a new CoherentAnimation for logo. By default its aways pause.
    var coherentLogo = new CoherentAnimation();

    // Object definitions for animations
    // Properties of object:
    // seconds: How long in seconds will be the animation
    // left: move div element to -450px left or start from -450px left.
    // opacity: fade in or out to opacity 0.
    // ease: easing allows you to change the speed of your animation over time. F
    // You can see full list of easing effects on http://greensock.com/jump-start-js#easing
    // By default easing effect is linear
    var moveFromLeft = {seconds: 0.6, left: -450, opacity: 0,
                        ease: Circ.easeIn};
    var moveFromRight = {seconds: 0.6, right: -450, opacity: 0,
                         ease: Circ.easeIn};
    var moveFromTop = {seconds: 0.6, top: -400, opacity: 0, ease: Circ.easeIn};
    var moveFromDown = {seconds: 0.6, top: 'auto', bottom: -300, opacity: 0,
                        ease: Circ.easeIn};

    var moveFromTopBounce = {seconds: 1, top: -400, opacity: 0,
                             ease: Bounce.easeOut};
    var moveToBottomBounce = {seconds: 1, top: 100, opacity: 1};

    // Array with objects definition for animations
    var blink = [
      {seconds: 0.01, opacity: 1},
      {seconds: 0.1, opacity: 0},
      {seconds: 0.1, opacity: 1},
      {seconds: 0.1, opacity: 0},
      {seconds: 0.2, opacity: 1}
    ];

    var rotation = {seconds: 2, rotationY:360, ease:Power0.easeIn, repeat: -1};

    var fadeOut = [
      {seconds: 0.1, opacity: 0},
      {seconds: 0.1, display: 'none'}
    ];
    var fadeIn = [
      {seconds: 0.1, display: 'block'},
      {seconds: 0.1, opacity: 1}
    ];

    // This object contains methods which will be calls when some button of menu will be clicked.
    var btnsActions = {
      optionsGameBtn: function() {
        var optionsMenuShow = new CoherentAnimation();

        // caTo will run the animation from current object or DOM element values to the reach the sended values of animations. The method take object as argument whit properties:
        // selecttor: DOM element or object
        // anims: object or array of object to run animation
        // offset(optional): (default = +=0) — Controls the placement of the tween in the timeline (by default, it's the end of the timeline, like "+=0"). Use a number to indicate an absolute time in terms of seconds (or frames for frames-based timelines), or you can use a string with a "+=" or "-=" prefix to offset the insertion point relative to the END of the timeline. For example, "+=2" would place the tween 2 seconds after the end, leaving a 2-second gap. "-=2" would create a 2-second
        // caStaggerFrom tweens an array of targets to a common set of destination values, but staggers their start times by a specified amount of time, creating an evenly-spaced sequence.
        // caStaggerFrom take the same properties like caFrom method with one more named stagger.
        //stagger: Amount of time in seconds (or frames if the timeline is frames-based) to stagger the start time of each tween.
        optionsMenuShow.caTo({
          selector: '#menu-start',
          anims: fadeOut
        }).caTo({
          selector: '#menu-options',
          anims: fadeIn
        }).caStaggerFrom({
          selector: '#menu-options .btn',
          anims: moveFromTopBounce,
          stagger: 0.5
        }).play();
      },
      backToStartGameBtn: function() {
        var optionsMenuOut = new CoherentAnimation();
        // addCallback method will call the startMenu function after animation is complete
        optionsMenuOut.caStaggerTo({
          selector: '#menu-options .btn',
          anims: moveFromTopBounce,
          stagger: 0.5
        }).addCallback(startMenu).play();
      },
      startGameBtn: function() {},
      creditsGameBtn: function() {},
      quitGameBtn: function() {},
      videoGameBtn: function() {},
      audioGameBtn: function() {},
    };

    // Add event handler on all menu buttons and call function after animation is complete
    $('.menu .btn').on('click', function() {
      var blinkBtn = new CoherentAnimation();
      var actionFn = $(this).attr('data-action-fn');
      var tmpFn = btnsActions[actionFn];
      blinkBtn.caTo({
        selector: $(this),
        anims: blink
      }).addCallback(tmpFn).play();
    });

    function init() {
      coherentLogoAnim();
      startMenu();
    }

    function coherentLogoAnim() {
      coherentLogo.caTo({
        selector: '#logo-duration',
        anims: rotation
      }).play();
    }

    // set method reset all applyed inline style properties of element
    function startMenu() {
      var coherentMenu = new CoherentAnimation();
      coherentMenu.caTo({
        selector: '#menu-options',
        anims: fadeOut
      }).caTo({
        selector: '#menu-start',
        anims: fadeIn
      }).caFrom({
        selector: '#start-btn',
        anims: moveFromTop
      }).caFrom({
        selector: '#options-btn',
        anims: moveFromLeft,
        offset: '-=0.5'
      }).caFrom({
        selector: '#credits-btn',
        anims: moveFromRight,
        offset: '-=0.4'
      }).caFrom({
        selector: '#quit-btn',
        anims: moveFromDown,
        offset: '-=0.3'
      }).set('#menu-options .btn', {clearProps:'all'}).play();
    }

    init();
  });
})();
