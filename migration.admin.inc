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

  $form['migration_hook_update_pageviews'] = array(
    '#type' => 'radios',
    '#title' => t('hook_update_N pageviews'),
    '#description' => t('Display hook_update_N php code in the status message.'),
    '#options' => array(0 => 'Hide', 1 => 'Show'),
    '#default_value' => variable_get('migration_hook_update_pageviews', 0),
  );

  return system_settings_form($form);
}

/**
 * List of monitored tables.
 */
function migration_tables_list_form($form_state) {
  $form = array();

  $form['migration_filter_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Filter mode'),
    '#description' => t('Choose whether tables are included or excluded based on the selection below.'),
    '#options' => array(0 => 'Exclude', 1 => 'Include'),
    '#default_value' => variable_get('migration_filter_mode', 0),
  );

  $form['migration_database_tables'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Database tables'),
    '#description' => t('The description appears usually below the checkboxes.'),
    '#options' => migration_get_tables(),
    '#default_value' => variable_get('migration_database_tables', migration_get_default_tables()),
    '#checkall' => TRUE,
    '#multicolumn' => array('width' => 4),
  );
  $form['#submit'][] = 'migration_tables_list_form_submit';
  return system_settings_form($form);
}

function migration_tables_list_form_submit($form, &$form_state){
  if ($form_state['values']['migration_filter_mode'] == 1){
    variable_set('migration_database_table_settings', migration_reverse_valid_tables($form_state['values']['migration_database_tables']));
  }else{
    variable_set('migration_database_table_settings', $form_state['values']['migration_database_tables']);
  }
}


/**
 * Control the query monitor
 */
function migration_monitor_control($action) {
  $action = strtolower($action);

  if ($action == 'start') {
    variable_set('migration_query_monitor', TRUE);
    print drupal_json(array(
      'response' => 'Migration Query Monitor: RUNNING',
      'divHtml' => '<a href="#" id="migration-stop-monitor">Stop Query Monitor</a>',
    ));
  }
  elseif ($action == 'stop') {
    variable_set('migration_query_monitor', FALSE);
    print drupal_json(array(
      'response' => 'Migration Query Monitor: STOPPED',
      'divHtml' => '<a href="#" id="migration-start-monitor">Start Query Monitor</a>',
    ));
  }
  else {
    print drupal_json(array('response' => 'Unrecognized action for query monitor controller'));
  }
}

function migration_get_tables() {
  $query = db_query('SHOW TABLES');
  while ($row = db_result($query)) {
    $tables[$row] = $row;
  }
  return $tables;
}

function migration_reverse_valid_tables($table_array){
  foreach (array_keys($table_array) as $tablename){
    if ($table_array[$tablename] === $tablename){
      $table_array[$tablename] = 0;
    } else {
      $table_array[$tablename] = $tablename;
    }
  }
  return $table_array;
}
