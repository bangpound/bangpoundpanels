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
  'render pane' => 'panels_naked_style_render_pane',
  'settings form' => 'bangpoundpanels_vertical_tabs_style_settings_form',
  'settings validate' => 'bangpoundpanels_vertical_tabs_style_settings_validate',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundpanels_vertical_tabs_style_render_region($vars) {

  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $panes = array_reverse($vars['panes'], TRUE);
  $settings = $vars['settings'];

  //Build items and fieldset
  $items = array();
  $owner = $vars['owner_id'];

  $build[$owner] = array(
    '#type' => 'vertical_tabs',
    '#weight' => 99,
  );

  $delta = 1;
  foreach ($display->panels[$region_id] as $pane_id) {

    $title = bangpoundpanels_pane_titles($display->did, $pane_id);
    $title = $title ? $title : t('Tab @delta', array('@delta' => $delta));

    $pane_class = "pane_" . $pane_id;

    $build[$pane_class] = array(
      '#type' => 'fieldset',
      '#title' => $title,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => $owner,
      '#attributes' => array(
        'class' => array($pane_class),
      ),
      '#tree' => TRUE,
      '#weight' => -2,
    );

    $build[$pane_class]['items'] = array(
      '#markup' => $panes[$pane_id],
    );
    $delta++;
  }

  return theme($settings['tabs_type'], array(
      'element' => array(
        '#children' => render($build),
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
