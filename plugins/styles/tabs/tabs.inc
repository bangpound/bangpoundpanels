<?php


/**
 * @file
 * Definition of the 'Tabs' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Tabs'),
  'description' => t('Show panel panes in a region as tabs.'),
  'render region' => 'bangpoundpanels_tabs_style_render_region',
  'render pane' => 'panels_pane__tabs',
  'pane style' => 'tabs',
  'hook theme' => 'bangpoundpanels_tabs_theme',
);

/**
 * Plugin's hook theme.
 *
 * Sets a template for the new pane theme.
 */
function bangpoundpanels_tabs_theme(&$theme, $data) {
  $theme['panels_pane__tabs']['template'] = 'panels-pane--tabs';
}

/**
 * Preprocess tabs pane.
 *
 * @see template_preprocess_panels_pane().
 */
function template_preprocess_panels_pane__tabs(&$variables, $hook) {

  $content = $variables['content'];

  if (!empty($content->css_id)) {
    $css_id = drupal_html_id($content->css_id);
  }
  else {
    $css_id = drupal_html_id($variables['pane']->panel);
  }
  $variables['attributes_array']['id'] = $css_id;

  template_preprocess_panels_pane($variables);

  $variables['classes_array'][] = 'pane-content';

  if (!empty($content->title_array) && isset($content->title_array['#title'])) {
    $title = $content->title_array['#title'];
  }
  else if (!empty($content->title_link)) {
    $title = filter_xss($content->title, array());
  }
  else if (!empty($content->title)) {
    $title = $content->title;
  }
  else {
    $title = t('Tab @delta', array('@delta' => $variables['pane']->position + 1));
  }
  $variables['title'] = '';
  $variables['attributes_array']['title'] = $title;
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundpanels_tabs_style_render_region($vars) {
  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $owner_id = $vars['owner_id'];
  $panes = $vars['panes'];

  $tab_id = 'tabs-' . $owner_id . '-' . $region_id;

  $element = array(
    '#prefix' => '<div id="' . $tab_id . '">',
    '#suffix' => '</div>',
    '#attached' => array(
      'library' => array(array('system', 'ui.tabs')),
      'js' => array(
        drupal_get_path('module', 'bangpoundpanels') . '/plugins/styles/tabs/tabs.js' => array('type' => 'file'),
      ),
    ),
  );

  $element['#attached']['js'][] = array(
    'type' => 'setting',
    'data' => array(
      'panelsTabs' => array(
        '#'. $tab_id => array(
        ),
      ),
    ),
  );

  foreach ($panes as $pane_id => $item) {
    $element['tabs_content'][$pane_id] = array(
      '#markup' => $item,
    );
  }

  return drupal_render($element);
}
