<?php
class views_plugin_style_rdf extends views_plugin_style {
  
  /**
   * Set default options
   */
  function options(&$options) {
    $options['vocabulary'] = 'FOAF';
  }
  
  /**
   * Provide a form for setting options.
   *
   * @param array $form
   * @param array $form_state
   */  
  function options_form(&$form, &$form_state) {
    $form['vocabulary'] = array(
      '#type' => 'radios',
      '#title' => t('RDF vocabulary'),
      '#options' => array('FOAF' => t('FOAF')),
      '#default_value' => $this->options['vocabulary'],
    );
  }

}