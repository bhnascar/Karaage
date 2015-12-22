/**
 * Adobe Edge: symbol definitions
 */
(function($, Edge, compId){
//images folder
var im='images/';

var fonts = {};
var opts = {
    'gAudioPreloadPreference': 'auto',

    'gVideoPreloadPreference': 'auto'
};
var resources = [
];
var symbols = {
"stage": {
    version: "4.0.1",
    minimumCompatibleVersion: "4.0.1",
    build: "4.0.1.365",
    baseState: "Base State",
    scaleToFit: "none",
    centerStage: "none",
    initialState: "Base State",
    gpuAccelerate: false,
    resizeInstances: false,
    content: {
            dom: [
            {
                id: 'RadianSymbol',
                type: 'rect',
                rect: ['245', '496','auto','auto','auto', 'auto']
            },
            {
                id: 'RbSymbol',
                type: 'rect',
                rect: ['646', '521','auto','auto','auto', 'auto']
            },
            {
                id: 'radiationSymbol',
                type: 'rect',
                rect: ['279', '221','auto','auto','auto', 'auto']
            }],
            symbolInstances: [
            {
                id: 'radiationSymbol',
                symbolName: 'atom',
                autoPlay: {

                }
            },
            {
                id: 'RbSymbol',
                symbolName: 'RbSymbol',
                autoPlay: {

                }
            },
            {
                id: 'RadianSymbol',
                symbolName: 'RadianSymbol',
                autoPlay: {

                }
            }
            ]
        },
    states: {
        "Base State": {
            "${_Stage}": [
                ["color", "background-color", 'rgba(0,0,0,0.00)'],
                ["style", "overflow", 'visible'],
                ["style", "height", '800px'],
                ["style", "width", '800px']
            ],
            "${_RadianSymbol}": [
                ["style", "left", '87px'],
                ["style", "top", '504px']
            ],
            "${_radiationSymbol}": [
                ["style", "left", '316px'],
                ["style", "top", '225px']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 41000,
            autoPlay: true,
            timeline: [
                { id: "eid4", tween: [ "style", "${_radiationSymbol}", "top", '225px', { fromValue: '225px'}], position: 0, duration: 0 },
                { id: "eid3", tween: [ "style", "${_radiationSymbol}", "left", '316px', { fromValue: '316px'}], position: 0, duration: 0 }            ]
        }
    }
},
"RadianSymbol": {
    version: "4.0.1",
    minimumCompatibleVersion: "4.0.1",
    build: "4.0.1.365",
    baseState: "Base State",
    scaleToFit: "none",
    centerStage: "none",
    initialState: "Base State",
    gpuAccelerate: false,
    resizeInstances: false,
    content: {
            dom: [
                {
                    rect: ['0px', '0px', '342px', '56px', 'auto', 'auto'],
                    borderRadius: ['10px', '10px', '10px', '10px'],
                    id: 'RadiationLevelCopy6',
                    stroke: [3, 'rgba(0,151,255,0.48)', 'solid'],
                    type: 'rect',
                    fill: ['rgba(0,151,255,0.25)', [270, [['rgba(0,151,255,1.00)', 0], ['rgba(255,255,255,1.00)', 100]]]]
                },
                {
                    type: 'text',
                    rect: ['9px', '7px', '194px', 'auto', 'auto', 'auto'],
                    id: 'Radiation_TextCopy6',
                    text: 'Radiation Level',
                    align: 'left',
                    font: ['Verdana, Geneva, sans-serif', 18, 'rgba(255,255,255,1)', 'normal', 'none', 'normal']
                },
                {
                    rect: ['9px', '34px', '274px', '12px', 'auto', 'auto'],
                    id: 'RadiationStatusBackgroundCopy6',
                    stroke: [3, 'rgba(0,151,255,0.00)', 'solid'],
                    type: 'rect',
                    fill: ['rgba(0,151,255,0.26)']
                },
                {
                    rect: ['9px', '34px', '0px', '18px', 'auto', 'auto'],
                    id: 'RadiationStatusCopy5',
                    stroke: [0, 'rgba(0,151,255,0.00)', 'solid'],
                    type: 'rect',
                    fill: ['rgba(0,151,255,0.2461)', [180, [['rgba(0,151,255,1.00)', 0], ['rgba(0,92,156,1.00)', 100]]]]
                },
                {
                    id: 'atomic2Copy5',
                    type: 'image',
                    rect: ['299px', '14px', '37px', '36px', 'auto', 'auto'],
                    fill: ['rgba(0,0,0,0)', 'images/atomic.png', '0px', '0px']
                }
            ],
            symbolInstances: [
            ]
        },
    states: {
        "Base State": {
            "${_RadiationStatusBackgroundCopy6}": [
                ["color", "background-color", 'rgba(0,151,255,0.2539)'],
                ["style", "top", '34px'],
                ["color", "border-color", 'rgba(0, 151, 255, 0)'],
                ["style", "left", '9px'],
                ["style", "width", '274px']
            ],
            "${_RadiationLevelCopy6}": [
                ["color", "background-color", 'rgba(0,151,255,0.2461)'],
                ["style", "border-style", 'solid'],
                ["style", "border-width", '3px'],
                ["style", "width", '342px'],
                ["style", "top", '0px'],
                ["style", "height", '56px'],
                ["color", "border-color", 'rgba(0, 151, 255, 0.476563)'],
                ["gradient", "background-image", [270,[['rgba(255,255,255,0.00)',0],['rgba(255,255,255,0.00)',100]]]],
                ["style", "left", '0px']
            ],
            "${symbolSelector}": [
                ["style", "height", '62px'],
                ["style", "width", '348px']
            ],
            "${_atomic2Copy5}": [
                ["style", "top", '14px'],
                ["style", "height", '36px'],
                ["style", "left", '299px'],
                ["style", "width", '37px']
            ],
            "${_RadiationStatusCopy5}": [
                ["style", "top", '34px'],
                ["color", "background-color", 'rgba(255,0,0,0.25)'],
                ["style", "left", '9px'],
                ["color", "border-color", 'rgba(0, 151, 255, 0)'],
                ["style", "height", '18px'],
                ["gradient", "background-image", [180,[['rgba(0,151,255,1.00)',0],['rgba(0,92,156,1.00)',100]]]],
                ["style", "border-width", '0px'],
                ["style", "width", '0px']
            ],
            "${_Radiation_TextCopy6}": [
                ["style", "top", '7px'],
                ["style", "width", '194px'],
                ["style", "left", '9px'],
                ["style", "font-size", '18px']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 41000,
            autoPlay: true,
            timeline: [
            ]
        }
    }
},
"RbSymbol": {
    version: "4.0.1",
    minimumCompatibleVersion: "4.0.1",
    build: "4.0.1.365",
    baseState: "Base State",
    scaleToFit: "none",
    centerStage: "none",
    initialState: "Base State",
    gpuAccelerate: false,
    resizeInstances: false,
    content: {
            dom: [
                {
                    rect: ['52px', '1px', '58px', '28px', 'auto', 'auto'],
                    borderRadius: ['10px 10px', '54px 54px', '10px', '10px'],
                    id: 'RightButton',
                    stroke: [3, 'rgba(0,151,255,0.49)', 'solid'],
                    type: 'rect',
                    fill: ['rgba(0,151,255,0.2461)', [270, [['rgba(0,151,255,1.00)', 0], ['rgba(255,255,255,1.00)', 100]]]]
                },
                {
                    font: ['Verdana, Geneva, sans-serif', 18, 'rgba(255,255,255,1)', '400', 'none', 'normal'],
                    type: 'text',
                    id: 'RightButtonText',
                    text: 'RB',
                    align: 'left',
                    rect: ['61px', '7px', 'auto', 'auto', 'auto', 'auto']
                },
                {
                    type: 'rect',
                    id: 'RightButtonLine',
                    stroke: [0, 'rgba(0,151,255,0.00)', 'solid'],
                    rect: ['0px', '46px', '117px', '4px', 'auto', 'auto'],
                    fill: ['rgba(0,151,255,0.2461)', [0, [['rgba(0,151,255,1.00)', 0], ['rgba(0,92,156,1.00)', 100]]]]
                },
                {
                    id: 'Symbol_2Copy3',
                    type: 'rect',
                    rect: ['-355px', '-135px', 'auto', 'auto', 'auto', 'auto'],
                    transform: [[0, 0], [], [], ['0.11683', '0.11683']]
                },
                {
                    type: 'rect',
                    id: 'RightButtonInfoTextBGCopy',
                    stroke: [0, 'rgba(0, 151, 255, 0)', 'solid'],
                    rect: ['0px', '53px', '117px', '37px', 'auto', 'auto'],
                    fill: ['rgba(0,151,255,0.00)', [270, [['rgba(0,151,255,0.65)', 0], ['rgba(255,255,255,0.00)', 58]]]]
                },
                {
                    font: ['Verdana, Geneva, sans-serif', 18, 'rgba(255,255,255,1)', '400', 'none', 'normal'],
                    type: 'text',
                    id: 'RightButtonInfoText',
                    text: 'scan',
                    align: 'left',
                    rect: ['3px', '50px', 'auto', 'auto', 'auto', 'auto']
                }
            ],
            symbolInstances: [
            {
                id: 'Symbol_2Copy3',
                symbolName: 'Symbol_2',
                autoPlay: {

               }
            }            ]
        },
    states: {
        "Base State": {
            "${_RightButtonLine}": [
                ["style", "top", '46px'],
                ["color", "border-color", 'rgba(0,151,255,0.00)'],
                ["style", "left", '0px'],
                ["transform", "rotateZ", '0deg'],
                ["style", "height", '4px'],
                ["gradient", "background-image", [0,[['rgba(0,151,255,1.00)',0],['rgba(0,92,156,1.00)',100]]]],
                ["style", "border-width", '0px'],
                ["style", "width", '117px']
            ],
            "${_Symbol_2Copy3}": [
                ["style", "top", '-133px'],
                ["transform", "scaleY", '0.11683'],
                ["transform", "rotateZ", '-1deg'],
                ["transform", "scaleX", '0.11683'],
                ["style", "left", '-130px']
            ],
            "${symbolSelector}": [
                ["style", "height", '90px'],
                ["style", "width", '117px']
            ],
            "${_RightButtonText}": [
                ["style", "top", '7px'],
                ["style", "font-weight", '400'],
                ["style", "left", '61px'],
                ["style", "font-size", '18px']
            ],
            "${_RightButton}": [
                ["color", "background-color", 'rgba(0,151,255,0.2461)'],
                ["style", "border-top-left-radius", [10,10], {valueTemplate:'@@0@@px @@1@@px'} ],
                ["style", "border-style", 'solid'],
                ["style", "border-width", '3px'],
                ["style", "width", '58px'],
                ["style", "top", '1px'],
                ["style", "right", 'auto'],
                ["style", "left", '52px'],
                ["style", "height", '28px'],
                ["color", "border-color", 'rgba(0, 151, 255, 0.484375)'],
                ["gradient", "background-image", [270,[['rgba(255,255,255,0.00)',0],['rgba(255,255,255,0.00)',100]]]],
                ["style", "border-top-right-radius", [54,54], {valueTemplate:'@@0@@px @@1@@px'} ]
            ],
            "${_RightButtonInfoTextBGCopy}": [
                ["color", "background-color", 'rgba(0,151,255,0.00)'],
                ["gradient", "background-image", [270,[['rgba(0,151,255,0.65)',0],['rgba(255,255,255,0.00)',58]]]],
                ["style", "left", '0px'],
                ["style", "top", '53px']
            ],
            "${_RightButtonInfoText}": [
                ["style", "top", '50px'],
                ["style", "font-weight", '400'],
                ["style", "left", '3px'],
                ["style", "font-size", '18px']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 0,
            autoPlay: true,
            timeline: [
            ]
        }
    }
},
"Symbol_2": {
    version: "4.0.1",
    minimumCompatibleVersion: "4.0.1",
    build: "4.0.1.365",
    baseState: "Base State",
    scaleToFit: "none",
    centerStage: "none",
    initialState: "Base State",
    gpuAccelerate: false,
    resizeInstances: false,
    content: {
            dom: [
                {
                    id: 'loadingCricle1',
                    type: 'image',
                    rect: ['0px', '0px', '300px', '302px', 'auto', 'auto'],
                    fill: ['rgba(0,0,0,0)', 'images/loadingCricle1.png', '0px', '0px']
                },
                {
                    type: 'image',
                    id: 'loadingCricle2',
                    opacity: 1,
                    rect: ['0px', '0px', '300px', '302px', 'auto', 'auto'],
                    fill: ['rgba(0,0,0,0)', 'images/loadingCricle2.png', '0px', '0px']
                },
                {
                    type: 'image',
                    id: 'loadingCricle3',
                    opacity: 1,
                    rect: ['0px', '0px', '300px', '302px', 'auto', 'auto'],
                    fill: ['rgba(0,0,0,0)', 'images/loadingCricle3.png', '0px', '0px']
                }
            ],
            symbolInstances: [
            ]
        },
    states: {
        "Base State": {
            "${_loadingCricle1}": [
                ["style", "top", '0px'],
                ["style", "opacity", '1'],
                ["style", "left", '0px'],
                ["transform", "rotateZ", '0deg']
            ],
            "${_loadingCricle2}": [
                ["style", "top", '0px'],
                ["style", "opacity", '1'],
                ["style", "left", '0px'],
                ["transform", "rotateZ", '0deg']
            ],
            "${_loadingCricle3}": [
                ["style", "top", '0px'],
                ["style", "opacity", '1'],
                ["style", "left", '0px'],
                ["transform", "rotateZ", '0deg']
            ],
            "${symbolSelector}": [
                ["style", "height", '302px'],
                ["style", "width", '300px']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 0,
            autoPlay: true,
            timeline: [
            ]
        }
    }
},
"atom": {
    version: "4.0.1",
    minimumCompatibleVersion: "4.0.1",
    build: "4.0.1.365",
    baseState: "Base State",
    scaleToFit: "none",
    centerStage: "none",
    initialState: "Base State",
    gpuAccelerate: false,
    resizeInstances: false,
    content: {
            dom: [
                {
                    id: 'atomic',
                    type: 'image',
                    rect: ['0px', '0px', '167px', '159px', 'auto', 'auto'],
                    fill: ['rgba(0,0,0,0)', 'images/atomic.png', '0px', '0px']
                }
            ],
            symbolInstances: [
            ]
        },
    states: {
        "Base State": {
            "${_atomic}": [
                ["style", "top", '0px'],
                ["style", "left", '0px']
            ],
            "${symbolSelector}": [
                ["style", "height", '159px'],
                ["style", "width", '167px']
            ]
        }
    },
    timelines: {
        "Default Timeline": {
            fromState: "Base State",
            toState: "",
            duration: 0,
            autoPlay: true,
            timeline: [
            ]
        }
    }
}
};


Edge.registerCompositionDefn(compId, symbols, fonts, resources, opts);

/**
 * Adobe Edge DOM Ready Event Handler
 */
$(window).ready(function() {
     Edge.launchComposition(compId);
});
})(jQuery, AdobeEdge, "EDGE-26097234");
