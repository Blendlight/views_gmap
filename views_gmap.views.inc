<?php
/**
* Implements hook_views_plugins().
*/
function views_gmap_views_plugins() {
    $module_path = drupal_get_path('module', 'views_gmap');
    dsm($module_path);
    return array(
        'style' => array(
            'views_views_gmap_plugin_style' => array(
                'title' => t('views_gmap: Google Map'),
                'help' => t('Google Map style'),
                'path' => $module_path . '/plugins/views_gmap',
                'handler' => 'ViewsViewsGmapPluginStyle',
                'parent' => 'default',
                'theme' => 'views_views_gmap_plugin_style',
                'theme path' => $module_path . '/templates/views_gmap',
                'theme file' => 'theme.inc',
                'uses grouping' => TRUE,
                'uses options' => TRUE,
                'type' => 'normal')
        )
    );
}



