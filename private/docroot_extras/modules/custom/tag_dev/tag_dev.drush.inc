<?php

/**
 * @file
 * Custom Drush integration.
 */

/**
 * Implements hook_drush_command().
 *
 * @return
 *   An associative array describing your command(s).
 */
function tag_dev_drush_command() {
  return array(
    'golocal' => array(
      'description' => dt('Puts your site in local development mode.'),
    ),
    'godev' => array(
      'description' => dt('Puts your site in remote development mode.'),
    ),
    'gotest' => array(
      'description' => dt('Puts your site in remote testing mode.'),
    ),
  );
}

/**
 * Put the site in Acquia testing server mode.
 */
function drush_tag_dev_gotest() {
  drush_tag_dev_golocal();
}

/**
 * Put the site in Acquia development server mode.
 */
function drush_tag_dev_godev() {
  drush_tag_dev_golocal();
}

/**
 * Put the site in local development mode.
 */
function drush_tag_dev_golocal() {
  // Enable dev friendly modules.
  $modules_to_enable = array(
    'devel',
    'kint',
  );

  foreach ($modules_to_enable as $module) {
    \Drupal::service('module_installer')->install([$module]);

    if (\Drupal::moduleHandler()->moduleExists($module)) {
      drush_log(dt('@module enabled', array('@module' => $module)), 'ok');
    }
    else {
      drush_log(dt('@module not enabled!', array('@module' => $module)), 'error');
    }
  }

  // Disable any production modules.
  $disable = array();
  foreach ($disable as $module) {
    \Drupal::service('module_installer')->uninstall([$module]);

    if (\Drupal::moduleHandler()->moduleExists($module)) {
      drush_log(dt('@module failed to uninstall!', array('@module' => $module)), 'error');
    }
    else {
      drush_log(dt('@module correctly disabled!', array('@module' => $module)), 'ok');
    }
  }

  // Allow everyone to see devel messages like dpm().
  if (\Drupal::moduleHandler()->moduleExists('devel')) {
    $role = \Drupal\user\Entity\Role::load('authenticated');
    $role->grantPermission('access devel information');
    $role->save();

    $role = \Drupal\user\Entity\Role::load('anonymous');
    $role->grantPermission('access devel information');
    $role->save();
  }

  // Setup configs for developers.
  // Note: If you get errors relating to immutablility, you need use a
  // a different config set.
  $dev_configs = array(
    ['devel.settings', 'devel_dumper', 'kint'],
  );

  foreach ($dev_configs as $key => $value) {
    list($config, $field, $field_value) = $value;

    \Drupal::service('config.factory')
      ->getEditable($config)
      ->set($field, $field_value)
      ->save();
  }

  drupal_flush_all_caches();
  drush_log('All caches cleared.', 'ok');

  drush_log('Site ready for development!', 'ok');
}
