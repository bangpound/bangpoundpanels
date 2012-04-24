<?php

// Plugin definition
$plugin = array(
  'title' => t('Accordion style'),
  'description' => t('Display panes as accordion.'),
  'render region' => 'bangpoundpanels_accordion_style_render_region',
  'settings form' => 'bangpoundpanels_accordion_style_settings_form',
  'weight' => -15,
);

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
  	$region_id = 'accordion-panels-' . $region_id ;
  } else {
  	$region_id = 'accordion-' . $display->css_id ;
  }

  $output = '';
  $output .= '<div id="'. $region_id .'" class="region region-' . $vars['region_id'] . '">';

  $items = array();
  $delta = 1;
  foreach ($display->panels[$vars['region_id']] as $pane_id) {
    // Make sure the pane exists.
    if (!empty($panes[$pane_id])) {
      $title = bangpoundpanels_pane_titles($display->did, $pane_id);

      if (!is_array($title)) {
        $title = array(
          '#type' => 'link',
          '#title' => $title,
          '#href' => '#',
          '#options' => array(
            'absolute' => TRUE,
            'external' => TRUE,
          ),
        );
      }

      $output .= '<h3 class="pane-title">';
      $output .= $title ? render($title) : t('Tab @delta', array('@delta' => $delta));
      $output .= '</h3>';
      $output .= '<div>';
      $output .= $panes[$pane_id];
      $output .= '</div>';
      ++$delta;
    }
  }

  $output .= '</div>';

  $settings['header'] = '.pane-title';
  $settings['active'] = (int) $settings['active'];

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
  	'#options' => array('click' => t('On click'),'mouseover' => t('On mouse over')),
    '#default_value' => (isset($style_settings['event'])) ? $style_settings['event'] : 'click',
  );
  $form['fillSpace'] = array(
    '#type' => 'checkbox',
    '#title' => t('If set, the accordion completely fills the height of the parent element. Overrides autoheight.'),
  	'#return_value' => true,
    '#default_value' => (isset($style_settings['event'])) ? $style_settings['event'] : false,
  );
  $form['navigation'] = array(
    '#type' => 'checkbox',
    '#title' => t('If set, looks for the anchor that matches location.href and activates it. Great for href-based state-saving. Use navigationFilter to implement your own matcher..'),
  	'#return_value' => true,
    '#default_value' => (isset($style_settings['navigation'])) ? $style_settings['navigation'] : false,
  );

  return $form;
}
