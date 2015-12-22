/*
This file is part of Coherent UI, modern user interface library for
games. Release $RELEASE$. Build $VERSION$ for $LICENSEE$.

Copyright (c) 2012-2014 Coherent Labs AD and/or its licensors. All
rights reserved in all media.

The coded instructions, statements, computer programs, and/or related
material (collectively the "Data") in these files contain confidential
and unpublished information proprietary Coherent Labs and/or its
licensors, which is protected by United States of America federal
copyright law and by international treaties.

This software or source code is supplied under the terms of a license
agreement and nondisclosure agreement with Coherent Labs Limited and may
not be copied, disclosed, or exploited except in accordance with the
terms of that agreement. The Data may not be disclosed or distributed to
third parties, in whole or in part, without the prior written consent of
Coherent Labs Limited.

COHERENT LABS MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS
SOURCE CODE FOR ANY PURPOSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER, ITS AFFILIATES,
PARENT COMPANIES, LICENSORS, SUPPLIERS, OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OR PERFORMANCE OF THIS SOFTWARE OR SOURCE CODE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
(function() {
  'use strict';

  /* exported GameOptions */
  /* global $ */
  /* global jQuery */
  /* global Handlebars */

  (function($) {

    var repeat = function(what, num) {
      return new Array(num + 1).join(what);
    };

    //Add segments to a slider
    $.fn.addSliderSegments = function (amount) {
      return this.each(function () {
        var segmentGap = 100 / (amount - 1) + '%',
            segment = '<div class="ui-slider-segment" style="margin-left: ' +
            segmentGap + ';></div>';
        $(this).prepend(repeat(segment, amount - 2));
      });
    };
  })(jQuery);

  (function() {

    var templates,
        gameMenuHtml,
        sliderHbsHtml,
        checkBoxHbsHtml,
        colorpickerCUIHbsHtml,
        selectHbsHtml,
        numberHbsHtml,
        countInstance = 0,
        optionTypes = {
          slider: new CuiSlider(),
          checkbox: new CuiCheckbox(),
          colorpickerCUI: new CuiColorpickerCUI(),
          select: new CuiSelect(),
          number: new CuiNumber()
        },
        loadedTemplates = $.when(loadTemplate('gameMenu.html'),
                                 loadTemplate('slider.hbs'),
                                 loadTemplate('checkbox.hbs'),
                                 loadTemplate('colorpickerCUI.hbs'),
                                 loadTemplate('select.hbs'),
                                 loadTemplate('number.hbs')
                                );

	/*
		options.gameOptions - array of options. Each option has:
		- id
		- name - label for the option
		- type - possible types are `slider`, `checkbox`, `colorpickerCUI`,
		  `select`, `number`
		options.saveCallback - called when the 'Save' button is clicked. If
		`options.saveCallback` returns true, the changes are saved, otherwise
		the changes are discarded.
		options.cancelCallback - called when the 'Cancel' button is clicked
		options.parentEl - parent element for the options dialog
	*/
    var GameOptions = function(options) {

      this.parentEl = options.menuParentEL;
      this.optionsParams = options.gameOptions;
      this.cancelCallback = options.callbackCancel;
      this.saveCallback = options.callbackSave;
      this.savedOptions = {};
      this._wrapperOptions = $('<div class="cui-wrapper-options"></div>');
      this._wrapperFrom = $('<div class="cui-wrapper-form"></div>');

      countInstance++;
      this._formClass = $('<form class="cui-options-form" options-form-id="' +
                          countInstance + '"></form>');

      this._createOptions();
      return this;
    };

    GameOptions.prototype._createOptions = function() {
      var _this = this;

      loadedTemplates.then(function(gameMenu, slider, checkbox, colorpickerCUI,
                                     select, number) {
        gameMenuHtml = gameMenu[0];
        sliderHbsHtml = slider[0];
        checkBoxHbsHtml = checkbox[0];
        colorpickerCUIHbsHtml = colorpickerCUI[0];
        selectHbsHtml = select[0];
        numberHbsHtml = number[0];

        _this._setHbsTemplates();
      }).done(function() {
        $(_this.parentEl).append(_this._wrapperOptions);
        $(_this._wrapperOptions).append(_this._wrapperFrom);
        $(_this._wrapperFrom).append(_this._formClass);

        var optionsLen = _this.optionsParams.length;
        for (var i = 0; i < optionsLen; i++) {
          var option = _this.optionsParams[i];
          $(_this._formClass)
          .append(_this._createFunction(option));
          var subOptions = option.subOptions;
          if(subOptions !== undefined) {
            var subOptionsLen = subOptions.length;
            for(var j = 0; j < subOptionsLen; j++) {
              $(_this._formClass)
              .append(_this._createFunction(subOptions[j]));
            }
          }
        }
        $(_this._formClass).append(gameMenuHtml);

        // Attach handlers to save and cancel buttons
        $(_this._formClass).on('click', '.cui-cancelButton',
                               _this._removeForm.bind(_this));
        $(_this._formClass).on('click', '.cui-saveButton',
                               _this._doSaveOptions.bind(_this));
      });
    };

    GameOptions.prototype.show = function() {
      $(this._wrapperOptions).css({display: 'table'});
      return this;
    };

    GameOptions.prototype.hide = function() {
      $(this._wrapperOptions).hide();
      return this;
    };

    GameOptions.prototype._removeForm = function() {
      this.cancelCallback();
    };

    GameOptions.prototype._doSaveOptions = function() {
      var _this = this;

      $(_this._formClass).find('.option').each(function() {
        var elDataAttr = $(this).find('label').data();
        var elTypeName = elDataAttr.cuiOptionType;
        var elLabel = elDataAttr.cuiId;

        // Save choosed option
        _this.savedOptions[elLabel] = optionTypes[elTypeName]
        ._save(_this._formClass, elLabel);
      });

      if (this.saveCallback(_this.savedOptions)) {
        this.saveCallbackObj = _this.savedOptions;
      } else {
        $(this._formClass).show();
      }
    };

    GameOptions.prototype._setHbsTemplates = function() {
      templates = {
        'slider': Handlebars.compile(sliderHbsHtml),
        'checkbox': Handlebars.compile(checkBoxHbsHtml),
        'colorpickerCUI': Handlebars.compile(colorpickerCUIHbsHtml),
        'select': Handlebars.compile(selectHbsHtml),
        'number': Handlebars.compile(numberHbsHtml)
      };
    };

    GameOptions.prototype._createFunction = function(option) {
      option.currentValue = getValue(option);
      var createElements = $(templates[option.type](option));

      // Create option control
      return optionTypes[option.type]._create(this, createElements, option);
    };

    // Slider Class
    function CuiSlider() {
      return this;
    }

    CuiSlider.prototype._create = function(menu, element, option) {

      var $thisOptionForm = $(menu._formClass);
      var max = option.values.length - 1;
      var maxSegments = max + 1;
      var slider = element.children()[0].children[1];

      var value;
      if(option.currentValue === undefined) {
        value = setOptions[option.id] || option.defaultVal;
      } else {
        value = option.currentValue;
        var infoEl = element.children()[0].children[2];
        $(infoEl).html(value);
      }

      var sliderPositionValue = option.values.indexOf(value);
      $(slider).slider({
        min: 0,
        max: max,
        value: sliderPositionValue,
        step: 1,
        orientation: 'horizontal',
        range: 'min',
        slide: function(event, ui) {
          var sliderInfoId;
          var sliderValue;
          if(option.subOptions){
            var setFieldValueFunc = function setFieldValues(fieldValues) {
              for(var subI = 0; subI < fieldValues.length; subI++){

                if (fieldValues[subI].presets) {
                  var optionPresets = fieldValues[subI].presets[0];
                  var fieldValueForDisplay;
                  for(var pres in optionPresets) {
                    if (pres == optionValue) {
                      fieldValueForDisplay = optionPresets[pres];
                      $thisOptionForm
                      .find('[cui-input-number-id=' +
                            option.subOptions[subI].id + ']')
                      .val(fieldValueForDisplay);
                    }
                  }
                }
              }
            };
            var optionValue = '';
            sliderInfoId = '.cui-sliderInfo' + option.id;
            sliderValue = ui.value;
            $thisOptionForm.find(sliderInfoId)
            .html(option.values[sliderValue]);
            optionValue = option.values[sliderValue];
            setFieldValueFunc(option.subOptions);
          } else {
            sliderInfoId = '.cui-sliderInfo' + option.id;
            sliderValue = ui.value;
            $thisOptionForm.find(sliderInfoId)
            .html(option.values[sliderValue]);
          }
        }
      }).addSliderSegments(maxSegments);

      return element;
    };

    CuiSlider.prototype._save = function(menu, elTitle) {
      var elTextValue = $(menu)
      .find('[data-cui-id="' + elTitle + '"]').next()
      .next('span').text();
      return elTextValue;
    };

    // Checkbox Class
    function CuiCheckbox() {
      return this;
    }

    CuiCheckbox.prototype._create = function(menu, element, option) {
      var checkbox = element.children()[0].children[1]
      .children[0].children[0];

      if(option.currentValue !== undefined) {
        if((option.currentValue == 'on') ||
           (option.currentValue == 'checked')) {
          $(checkbox).attr('checked','checked');
        } else {
          $(checkbox).removeAttr('checked');
        }
      }

      $(checkbox).wrap('<div class="switch" />').parent().bootstrapSwitch();
      return element;
    };

    CuiCheckbox.prototype._save = function(menu, elTitle) {
      var elTextValueArr = $(menu)
      .find('[data-cui-id="' + elTitle + '"]').next()
      .find('div.switch-animate').attr('class').split(' ');

      var elTextValue;
      for(var i = 0; i < elTextValueArr.length; i++){
        if((elTextValueArr[i] === 'switch-on') ||
           (elTextValueArr[i] === 'switch-off')){
          elTextValue = elTextValueArr[i].split('-')[1];
        }
      }
      return elTextValue;
    };

    // ColorpickerCUI Class
    function CuiColorpickerCUI() {
      return this;
    }

    CuiColorpickerCUI.prototype._create = function(menu, element, option) {
      var _this = menu;
      var colorPickerId = option.id;
      var colorSelector = element.children()[0].children[1]
      .children[0].children[0];

      var valueToUpdate = option.currentValue;

      if(option.currentValue !== undefined){
        $(colorSelector).css('background-color', valueToUpdate);
        option.color = valueToUpdate;
      }
      $(colorSelector).ColorPicker({
        color: '' + option.color + '',
        onShow: function(colpkr) {
          $(colpkr).stop(true, true).fadeIn(500);
          return false;
        },
        onHide: function (colpkr) {
          $(colpkr).stop(true, true).fadeOut(500);
          return false;
        },
        onChange: function(hsb, hex) {
          $(_this._formClass).find('.colorSelector div')
          .css('backgroundColor', '#' + hex);
        }
      });
      return element;
    };

    CuiColorpickerCUI.prototype._save = function(menu, elTitle) {
      var elTextValue = $(menu)
      .find('[data-cui-id="'  + elTitle + '"]')
      .next().find('.colorSelector')
      .children().css('background-color');

      function rgb2hex(rgb) {
        var hexDigits = '0123456789abcdef';
        rgb = rgb.match(/^rgb\((\d+),\s*(\d+),\s*(\d+)\)$/);
        function hex(x) {
          return isNaN(x) ? '00' : hexDigits[(x - x % 16) / 16] +
            hexDigits[x % 16];
        }
        return '#' + hex(rgb[1]) + hex(rgb[2]) + hex(rgb[3]);
      }

      var hexed = (rgb2hex(elTextValue));
      return hexed;
    };

    // Select Class
    function CuiSelect() {
      return this;
    }

    CuiSelect.prototype._create = function(menu, element, option) {
      var selectEl = element.children()[0].children[1].children[0];
      for(var i = 0; i < option.options.length; i++){
        $(selectEl).append('<option value="' + i + '">' +
                           option.options[i] + '</option>');
      }

      var valueToUpdate = option.currentValue;
      if(option.currentValue !== undefined) {
        $(selectEl).find('option[value="' + valueToUpdate + '"]')
        .attr('selected','selected');
      }

      $(selectEl).selectpicker({style: 'btn-primary',
                                menuStyle: 'dropdown-inverse'});
      return element;
    };

    CuiSelect.prototype._save = function(menu, elTitle) {
      var elTextValue = $(menu)
      .find('[data-cui-id="' + elTitle + '"]').next()
      .find('select').val();
      return elTextValue;
    };

    // Number Class
    function CuiNumber() {
      return this;
    }

    CuiNumber.prototype._create = function(menu, element, option) {
      var selectEl = element.children()[0].children[1];
      var valueToUpdate = option.currentValue;

      if(option.currentValue !== undefined) {
        $(selectEl).val(valueToUpdate);
      }
      return element;
    };

    CuiNumber.prototype._save = function(menu, elTitle) {
      var elTextValue = $(menu)
      .find('[data-cui-id="' + elTitle + '"]').next().val();
      return elTextValue;
    };

    function getValue(option) {
      var current = saveCallbackObj[option.id];
      return (current !== undefined)? current : option.defaultVal;
    }

    var saveCallbackObj = {};

    var setOptions = saveCallbackObj;

    function loadTemplate(name) {
      return $.get('../../lib/js/' + name);
    }

    window.GameOptions = GameOptions;
  })();
})();
