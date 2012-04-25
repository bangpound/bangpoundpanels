<?php

/**
 * @file
 * Definition of the 'vertical tabs' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Vertical tabs'),
  'description' => t('Presents the panes in a tabs fieldset.'),
  'render region' => 'bangpoundpanels_vertical_tabs_style_render_region',
  'render pane' => 'bangpoundpanels_vertical_tabs_style_render_pane',
  'settings form' => 'bangpoundpanels_vertical_tabs_style_settings_form',
  'settings validate' => 'bangpoundpanels_vertical_tabs_style_settings_validate',
  'pane style' => 'vertical_tabs',
);

/**
 * Render pane callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundpanels_vertical_tabs_style_render_pane($vars) {
  $content = $vars['content'];
  $display = $vars['display'];

  $owner = 0;
  if (isset($display->owner) && is_object($display->owner) && isset($display->owner->id)) {
    $owner = $display->owner->id;
  }

  $title = $content->title ? $content->title : t('Tab @delta', array('@delta' => $vars['pane']->position + 1));
  $element = array(
    '#type' => 'fieldset',
    '#title' => $title,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => $owner,
    '#tree' => TRUE,
    '#weight' => $vars['pane']->position + 1,
  );

  $pane_class = "pane_" . $vars['pane']->pid;
  $element['#attributes'] = array(
    'class' => array($pane_class),
  );

  $element[$pane_class] = array(
    '#children' => render($content->content),
  );
  return drupal_render($element);
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundpanels_vertical_tabs_style_render_region($vars) {
  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $panes = $vars['panes'];
  $settings = $vars['settings'];
  return theme($settings['tabs_type'], array(
      'element' => array(
        '#children' => implode($vars['panes']),
      ),
  ));
}

/**
 * Settings form callback.
 */
function bangpoundpanels_vertical_tabs_style_settings_form($style_settings) {
  //Vertical tabs are in core
  $options['vertical_tabs'] = t('Vertical');
  //field_group.module allows same structure, for horizontal tabs
  if (module_exists('field_group')) $options['horizontal_tabs'] = t('Horizontal');

  $form['tabs_type'] = array(
    '#type' => 'select',
    '#title' => t('Tabs type'),
    '#options' => $options,
    '#default_value' => (isset($style_settings['tabs_type'])) ? $style_settings['tabs_type'] : 'vertical_tabs',
  );

  return $form;
}
