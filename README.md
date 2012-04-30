!&# Panels
==========

This module takes excellent work from [Panopoly](http://drupal.org/project/panopoly) and
combines it into a single optional module. (Please forgive my anti-social behavior)

* Pane previews
* Override view mode of node rows in view content panes.
* UI improvements for pane settings: grouping of fields, relabeling, autocomplete filter
  on node titles.
* Use view modes in entity template suggestions.
* All of Panopoly's layout plugins.
* jQuery UI Accordion, jQuery UI Tabs and Drupal 7 Vertical Tab region style plugins.
* Contextual links to edit an entity's fields and its view mode display settings.
* No markup is default on all new panel displays and panes.

Style plugins
-------------

See <http://drupal.org/comment/reply/1101536#comment-5913990>.

Panopoly comes with a jQuery UI accordion style plugin that also tries to work around both
of these problems. I also incorporated the [Panels Tabs
project](http://drupal.org/project/panels_tabs) and this [Vertical Tabs plugin
patch](http://drupal.org/node/1101536#comment-5789436). These are three style plugins that
all confront the same problems.

1. Region styles and pane styles are completely distinct. Even though region styles
   and pane styles can coexist in the same plugin, when the display is rendered, they may
   as well be two completely different plugins.
2. The return value of `ctools_content_render()` and
   `panels_renderer_standard::render_pane_content()` has a short lifespan relative to the
   lifespan of the panel display. It doesn't survive beyond theming the individual panel
   pane.

**Drupal core vertical tabs** produce a fieldset-legend markup that is transformed by
jQuery. For this case, the region style needs to be able to control the styles of all the
panes within it so that the panes are all rendered as fieldsets with legends.

**Accordion** regions present a similar problem. The accordion region has to determine the
pane styles so that it can make assumptions about the markup. Otherwise, some contortions
to pass titles into the region theme layer are necessary.

**jQuery UI Tabs** originally appeared to depend on a particular markup pattern where the
tab titles are combined in an unordered list that precedes the tabbed panes. However,
jQuery UI Tabs have methods to dynamically add and remove tabs, so rather than contorting
the markup, I just add the panes using jQuery UI widget methods.

The vertical tabs patch on this issue failed to handle titles correctly. Panopoly
Accordion did similar things, apparently requiring an overridden title for the accordion
to work correctly. Panels Tabs did something more tedious: it stores titles in a static
cache during `hook_panels_pane_content_alter()` and later retrieved that title when the
region was being rendered. That's opaque.

A better solution is to allow region styles to specify a "pane style," which is the name
of the plugin that should be used for all panes in that region. During
[`hook_panels_pre_render`](https://github.com/bangpound/bangpoundpanels/blob/master/
bangpoundpanels.module#L505), loop through the panel settings to determine the style in
use for a given region. If that region has a pane style, the pane style overwrites the
style of all panes in that region. Currently, pane style settings are completely ignored
when the region's style enforces a "pane style." The plugin can specify itself as the pane
style, in which case the "render pane" callback needs to be written to produce the markup
your widget style needs.

* [jQuery UI Accordion][1]
* [jQuery UI Tabs][2]
* [Drupal 7 Vertical Tabs][3]
* [Implementation of `hook_panels_pre_render()`][4]

[1]: https://github.com/bangpound/bangpoundpanels/blob/master/plugins/styles/accordion/accordion.inc
[2]: https://github.com/bangpound/bangpoundpanels/blob/master/plugins/styles/tabs/tabs.inc
[3]: https://github.com/bangpound/bangpoundpanels/tree/master/plugins/styles/vertical_tabs
[4]: https://github.com/bangpound/bangpoundpanels/blob/master/bangpoundpanels.module#L505
