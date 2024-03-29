<?php

/**
 * @file
 * Views theme to render view fields as BibTeX.
 *
 * - $view: The view in use.
 * - $rows: Array of row objects as rendered by _views_bibtex_render_fields
 * - $attachment: Not used currently
 * - $options: The options for the style passed in from the UI.
 *
 * @ingroup views_templates
 * @see views_bibtex.views.inc
 */

function template_preprocess_views_views_bibtex_style_simple($vars) {
  $view = $vars["view"];
  $rows = $vars["rows"];
  $options = $vars["options"];
  $base = $view->base_table;
  $root_object = $options["root_object"];
  $top_child_object = $options["top_child_object"];
  $plaintext_output = $options["plaintext_output"];
  $objects = array();
  foreach ($rows as $row) {
    $object = array($top_child_object => array());
    /*Convert the $rows into a hierachial key=>value array*/
    foreach ($row as $field) {
      if ($options["field_output"] == "normal") {
        if ($field->label)
          $label = $plaintext_output ? strip_tags($field->label) : $field->label;
        else $label = $plaintext_output ? strip_tags($field->id) : $field->id;
        if (!$field->is_multiple) {
          $content = $plaintext_output ? strip_tags($field->content) : $field->content;
        }
        else {
          $content = array();
          foreach ($field->content as $n => $oc) $content[$n] = ($plaintext_output ? strip_tags($oc) : $oc);
        }
      }
      elseif ($options["field_output"] == "raw") {
        $label = $plaintext_output ? strip_tags($field->id) : $field->id;
        if (!$field->is_multiple) {
          $content = $plaintext_output ? strip_tags($field->raw) : $field->raw;
        }
        else {
          $content = array();
          foreach ($field->raw as $n => $oc) $content[$n] = $plaintext_output ? strip_tags($oc) : $oc;
        }
      }
      $object[$top_child_object][$label] = $content;
    }
    $objects[] = $object;
  }

  $vars["rows"] = array($root_object => $objects);
}
