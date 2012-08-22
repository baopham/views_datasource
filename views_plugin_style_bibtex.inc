<?php

/**
 * @file
 * Implementation of views_plugin_style for views_bibtex
 */


/**
 * Implementation of views_plugin_style
 */
class views_plugin_style_bibtex extends views_plugin_style {
  /**
   * Implementation of views_plugin_style::option_definition
   */
  function option_definition() {
    $options = parent::option_definition();
    // Always 'nodes'
    $options['root_object'] = array('default' => 'nodes', 'translatable' => FALSE);
    // Always 'node'
    $options['top_child_object'] = array('default' => 'node', 'translatable' => FALSE);
    $options['entry_type_label'] = array('default' => 'Entry type', 'translatable' => FALSE);
    $options['display_entry_type_field'] = array('default' => FALSE, 'translatable' => FALSE);
    $options['generate_key'] = array('default' => TRUE, 'translatable' => FALSE);
    // Always 'normal'
    $options['field_output'] = array('default' => 'normal', 'translatable' => FALSE);
    $options['plaintext_output'] = array('default' => TRUE, 'translatable' => FALSE);
    // There's only one format for now
    $options['format'] = array('default' => 'simple', 'translatable' => FALSE);
    $options['content_type'] = array('default' => 'default', 'translatable' => FALSE);
    $options['using_views_api_mode'] = array('default' => FALSE, 'translatable' => FALSE);
    return $options;
  }

  /**
   * Provide a form for setting options.
   *
   * @param $form
   * @param $form_state
   */
  function options_form(&$form, &$form_state) {
    $form['entry_type_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Entry type label'),
      '#description' => t('The label for the content field that indicates the entry type (Article, InProceedings, Book)'),
      '#default_value' => $this->options['entry_type_label'],
    );
    $form['display_entry_type_field'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display entry type field'),
      '#description' => t('If check, the entry type field will be displayed in the BibTeX'),
      '#default_value' => $this->options['display_entry_type_field'],
    );
    $form['generate_key'] = array(
      '#type' => 'checkbox',
      '#title' => t('Auto generate citation key'),
      '#description' => t('If checked, the citation key will be auto-generated. For example, author2009, author2010 ...'),
      '#default_value' => $this->options['generate_key'],
    );
    $form['plaintext_output'] = array(
      '#type'           => 'checkbox',
      '#title'          => ('Plaintext output'),
      '#default_value'  => $this->options['plaintext_output'],
      '#description'    => ('For each row in the view, strip all markup from the field output.'),
    );
    $form['content_type'] = array(
      '#type'           => 'radios',
      '#title'          => ('Content-Type'),
      '#options'        => array(
        'default'       => ("Default: text/plain"),
        'application/txt' => ('application/txt'),
      ),
      '#default_value'  => $this->options['content_type'],
      '#description'    => ('The Content-Type header that will be sent with the BibTeX output.')
    );
    $form['using_views_api_mode'] = array(
      '#type'           => 'checkbox',
      '#title'          => ('Views API mode'),
      '#default_value'  => $this->options['using_views_api_mode'],
      '#description'    => ('Not using View API mode means the BibTeX gets output directly and the server ceases normal page processing.  Using it means the server does not cease processing after outputting the BibTeX.  This allows the Views API to be used with the view without having to prematurely terminate page processing.'),
    );
  }

  /**
   * Implementation of view_style_plugin::theme_functions(). Returns an array of theme functions to use
   * for the current style plugin
   * @return array
   */
  function theme_functions() {
    $format = $this->options['format'];
    $hook = 'views_views_bibtex_style_' . $format;
    return views_theme_functions($hook, $this->view, $this->display);
  }

  /**
   * Implementation of views_style_plugin::additional_theme_functions(). Returns empty array.
   * @return array
   */
  function additional_theme_functions() {
    return array();
  }

  /**
   * Implementation of view_style_plugin::render()
   */
  function render() {
    $view = $this->view;
    $options = $this->options;
    $field = $view->field;

    $rows = array();

    foreach ($view->result as $row) {
      $rows[] = _views_bibtex_render_fields($view, $row);
    }

    return theme($this->theme_functions(), $view, $options, $rows);
  }

}

