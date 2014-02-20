/*jshint forin:true, noarg:true, noempty:true, eqeqeq:true, bitwise:true, undef:true, curly:true, browser:true, jquery:true, indent:2, maxerr:50 */
/*global Drupal:false, jQuery:false */
(function ($) {

  /**
   * JS related to the tabs in the Panels tabs.
   */
  Drupal.behaviors.panelsTabs = {
    addTab: function ($tabs, href, label, index) {
      var tabTemplate = "<li><a href='#{href}'>#{label}</a></li>",
        li = $(tabTemplate.replace(/#\{href\}/g, href).replace(/#\{label\}/g, label)),
        tabContentHtml = $(href);

      $tabs.find('.ui-tabs-nav').append(li);
      $tabs.append(tabContentHtml);
      $tabs.tabs('refresh');
    },
    attach: function (context, settings) {
      $.each(settings.panelsTabs, function (index) {
        var $tabs = $(index, context).prepend('<ul></ul>').tabs(this);

        $('.panel-pane', $tabs).once('panelsTabs', function (index) {
          var href = '#' + $(this).attr('id'),
            label = $(this).attr('title');
          Drupal.behaviors.panelsTabs.addTab($tabs, href, label, index);
        });

        $tabs.tabs('option', 'active', 0);
      });
    }
  };
})(jQuery);
