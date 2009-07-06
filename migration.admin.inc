<?php
// $Id$

/**
 * @file
 * Migration module administrative pages
 */


/**
 * Admin settings form.
 */
function migration_settings_form($form_state) {
  
  
  // Make sure our migration file exists
  $default_directory = file_directory_path() . '/migration';
  $status = file_check_directory($default_directory, FILE_CREATE_DIRECTORY, 'migration_directory_path');
  if (!$status) {
    $default_directory = '';
  }
  
  // Build the form
  $form = array();
  
  $form['migration_directory_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Migration Cache Path'),
    '#description' => t('Enter a writable directory where migration cache files are stored.'),
    '#default_value' => variable_get('migration_directory_path', $default_directory),
  );
  
  return system_settings_form($form);
}

/**
 * List of monitored tables.
 */
function migration_table_list_form($form_state) {
  $form = array();
  return system_settings_form($form);
}

/**
 * Control the query monitor
 */
function migration_monitor_control($action) {
  $action = strtolower($action);
  
  if ($action == 'start') {
    variable_set('migration_query_monitor', TRUE);
    print drupal_json(array('response' => 'Migration Query Monitor: RUNNING'));
  }
  elseif ($action == 'stop') {
    variable_set('migration_query_monitor', FALSE);
    print drupal_json(array('response' => 'Migration Query Monitor: STOPPED'));
  }
  else {
    print drupal_json(array('response' => 'Unrecognized action for query monitor controller'));
  }
}