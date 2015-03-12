window.addEventListener('load', function() {

  // First we bootstrap the Edge compositions with bootstrapCallback:
  AdobeEdge.bootstrapCallback(function(compId) {
    comp = AdobeEdge.getComposition(compId).getStage();
    init(comp);
  });

  var comp;
  var radiationStatusElem;
  var radiationLevelBackground;
  var blueCircleSymbol;
  var radiationSymbol;
  var leftBar;
  var rightBar;

  // This snippet of definition move progress bar of rariation level
  // With onUpdate property we call function checkLevel on every frame of
  // animation. checkLevel check the current width of progress bar and if
  // is > 200px play rlBackground snippet animation on radiationLevelBackground
  // symbol. If width is < 200px then reverse the rlBackground animation

  var rlWidth = [
    {seconds: 3, width: 280, onUpdate: checkLevel},
    {seconds: 3, width: 0, onUpdate: checkLevel}
  ];
  var rlBackground = {seconds: 0.5, backgroundColor: '#3F0000'};
  var  rotation = {seconds: 2, rotation:360, ease:Linear.easeNone, repeat: -1};

  var rl1 = new CoherentAnimation({repeat: -1});
  var rl2 = new CoherentAnimation();
  var rl3 = new CoherentAnimation();
  var rl4 = new CoherentAnimation({repeat: -1});

  var blink = [
    {seconds: 0.01, opacity: 1, delay: 1},
    {seconds: 0.1, opacity: 0},
    {seconds: 0.1, opacity: 1},
    {seconds: 0.1, opacity: 0},
    {seconds: 0.1, opacity: 1},
    {seconds: 2, delay: 2.6}
  ];

  function init(comp) {
    // Init adge symbols in DOM
    radiationStatusElem = comp.getSymbol('RadianSymbol')
                              .$('RadiationStatusCopy5');
    radiationLevelBackground = comp.getSymbol('RadianSymbol')
                              .$('RadiationLevelCopy6');
    blueCircleSymbol = comp.getSymbol('RbSymbol').$('Symbol_2Copy3');
    radiationSymbol = comp.$('radiationSymbol');

    // Play progress bar
    rl1.caTo({
      selector: radiationStatusElem,
      anims: rlWidth
    }).play();

    // Rotate circle
    rl3.caTo({
      selector: blueCircleSymbol,
      anims: rotation
    }).play();

    // Blink radiation symbol
    rl4.caTo({
      selector: radiationSymbol,
      anims: blink
    }).play();
    
    rl2 = rl2.caTo({
        selector: radiationLevelBackground,
        anims: rlBackground
      });
  }

  function checkLevel() {
    var currentPx = parseInt(radiationStatusElem[0].style.width);

    if (currentPx > 200) {
      rl2.play();
    } else {
      if (!rl2.reversed()) {
        rl2.reverse();
      }
    }
  }

}, false);
