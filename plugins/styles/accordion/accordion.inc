<?php

/**
 * @file
 * The accordian style plugin that is part of !&# Panels
 */

// Plugin definition
$plugin = array(
  'title' => t('Accordion style'),
  'description' => t('Display panes as accordion.'),
  'render region' => 'bangpoundpanels_accordion_style_render_region',
  'render pane' => 'panels_pane__accordion',
  'pane style' => 'accordion',
  'settings form' => 'bangpoundpanels_accordion_style_settings_form',
  'hook theme' => 'bangpoundpanels_accordion_theme',
  'weight' => -15,
);

/**
 * Plugin's hook theme.
 *
 * Sets a template for the new pane theme.
 */
function bangpoundpanels_accordion_theme(&$theme, $data) {
  $theme['panels_pane__accordion']['template'] = 'panels-pane--accordion';
}

/**
 * Preprocess accordion pane.
 *
 * @see template_preprocess_panels_pane().
 */
function template_preprocess_panels_pane__accordion(&$variables, $hook) {

  $content = clone($variables['content']);

  if (!empty($content->css_id)) {
    $css_id = drupal_html_id($content->css_id);
    $variables['attributes_array']['id'] = $css_id;
  }
  else {
    $css_id = drupal_html_id($variables['pane']->panel);
  }

  template_preprocess_panels_pane($variables);

  $title = $content->title;
  if (empty($content->title)) {
    $delta = $variables['pane']->position;
    $title = t('Tab @delta', array('@delta' => $delta));
  }
  else if (!empty($content->title_link)) {
    $title = filter_xss($content->title, array());
  }
  else if (!empty($content->title_array)) {
    $title = $content->title_array['#title'];
  }

  $variables['title'] = array(
    '#type' => 'link',
    '#title' => $title,
    '#href' => '#'. $css_id,
    '#options' => array(
      'absolute' => TRUE,
      'external' => TRUE,
    ),
  );

  $variables['title'] = render($variables['title']);

  if (!isset($variables['attributes_array']['class'])) {
    $variables['attributes_array']['class'] = array();
  }

  if (!empty($variables['classes_array'])) {
    $variables['attributes_array']['class'] = array_merge_recursive($variables['attributes_array']['class'], $variables['classes_array']);
  }

  if (!empty($variables['attributes_array'])) {
    $variables['content_attributes_array'] = array_merge_recursive($variables['content_attributes_array'], $variables['attributes_array']);
  }

}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_bangpoundpanels_accordion_style_render_region($vars) {
  // Include Some Basic Information
  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $panes = $vars['panes'];
  $settings = $vars['settings'];

  if (empty($display->css_id) ) {
    $region_id = drupal_html_id('accordion-panels-' . $region_id);
  }
  else {
    $region_id = drupal_html_id('accordion-' . $display->css_id);
  }

  // Display the Output
  $output = '';
  $output .= '<div id="'. $region_id .'">';
  $output .= implode($panes);
  $output .= '</div>';

  // Handle the Empty Placeholder Panels IPE Needs
  if (!empty($panes['empty_placeholder'])) {
    $output .= $panes['empty_placeholder'];
  }

  // Extend settings for jQuery UI accordion.
  $settings['header'] = '.pane-title';
  $settings['active'] = (int) $settings['active'];

  // Inject the Javascript
  drupal_add_library('system', 'ui.accordion');
  drupal_add_js(drupal_get_path('module', 'bangpoundpanels') .'/plugins/styles/accordion/accordion.js');
  drupal_add_js(array('accordion' => array('#'. $region_id => $settings)), 'setting');
  return $output;
}

function bangpoundpanels_accordion_style_settings_form($style_settings) {
  $form['active'] = array(
    '#type' => 'textfield',
    '#title' => t('Set active'),
    '#description' => t('Set to -1 if you want no pane active'),
    '#default_value' => (isset($style_settings['active'])) ? $style_settings['active'] : 0,
  );
  $form['autoHeight'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set to autoheight'),
    '#return_value' => 1,
    '#default_value' => (isset($style_settings['autoHeight'])) ? $style_settings['autoHeight'] : 1,
  );
  $form['clearStyle'] = array(
    '#type' => 'checkbox',
    '#description' => t("If set, clears height and overflow styles after finishing animations. This enables accordions to work with dynamic content. Won't work together with autoHeight."),
    '#title' => t('Clear heights after animation'),
    '#return_value' => 1,
    '#default_value' => (isset($style_settings['clearStyle'])) ? $style_settings['clearStyle'] : 0,
  );
  $form['collapsible'] = array(
    '#type' => 'checkbox',
    '#description' => t("Whether all the sections can be closed at once. Allows collapsing the active section by the triggering event (click is the default)."),
    '#title' => t('Can close all section'),
    '#return_value' => 1,
    '#default_value' => (isset($style_settings['collapsible'])) ? $style_settings['collapsible'] : 0,
  );
  $form['event'] = array(
    '#type' => 'select',
    '#title' => t('The event on which to trigger the accordion.'),
    '#options' => array('click' => t('On click'), 'mouseover' => t('On mouse over')),
    '#default_value' => (isset($style_settings['event'])) ? $style_settings['event'] : 'click',
  );
  $form['fillSpace'] = array(
    '#type' => 'checkbox',
    '#title' => t('If set, the accordion completely fills the height of the parent element. Overrides autoheight.'),
    '#return_value' => TRUE,
    '#default_value' => (isset($style_settings['event'])) ? $style_settings['event'] : FALSE,
  );
  $form['navigation'] = array(
    '#type' => 'checkbox',
    '#title' => t('If set, looks for the anchor that matches location.href and activates it. Great for href-based state-saving. Use navigationFilter to implement your own matcher..'),
    '#return_value' => TRUE,
    '#default_value' => (isset($style_settings['navigation'])) ? $style_settings['navigation'] : FALSE,
  );

  return $form;
}
