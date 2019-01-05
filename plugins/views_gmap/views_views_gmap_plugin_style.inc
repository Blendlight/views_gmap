<?php
/**
* @file
* Definition of views_views_gmap_plugin_style.
*/

/**
* Class to define a style plugin handler.
*/
class ViewsViewsGmapPluginStyle extends views_plugin_style {
    /**
  * Definition.
  */
    public function option_definition() {
        $options = parent::option_definition();

        $options['lat'] = array('default'=>'');

        $options['long'] = array('default'=>'');

        $options['popup_fields'] = array('default'=>[]);

        $options['c_lat'] = array('default'=>'');
        $options['c_long'] = array('default'=>'');
        
        $options['map_width'] = array('default'=>'500');
        $options['map_height'] = array('default'=>'400');
        
        return $options;
    }

    /**
  * Form.
  */
    function options_form(&$form, &$form_state) {
        parent::options_form($form, $form_state);

        if(isset($form['grouping'])){
            $options = array();
            foreach (element_children($form['grouping']) as $key => $value) {
                if (!empty($form['grouping'][$key]['field']['#options']) && is_array($form['grouping'][$key]['field']['#options'])) {
                    $options = array_merge($options, $form['grouping'][$key]['field']['#options']);
                }
            }

            $form['lat'] = array(
                '#type' => 'select',
                '#title' => t('Latitude Field'),
                '#options' => $options,
                '#required' => TRUE,
                '#default_value' => $this->options['lat'],
                '#description' => t('Select the field that will be used for latitude.'),
            );

            $form['long'] = array(
                '#type' => 'select',
                '#title' => t('Longitude Field'),
                '#options' => $options,
                '#required' => TRUE,
                '#default_value' => $this->options['long'],
                '#description' => t('Select the field that will be used for longitude.'),
            );

            $popoptions = array_slice($options, 1);
            $form['popup_fields'] = array(
                '#title' => 'Fields used in popup text',
                '#type' => 'checkboxes',
                '#options' => $popoptions,
                '#default_value' => $this->options['popup_fields'],
                '#description'=>'Select those fields which will be used as text in popup',
                '#attributes' => array('class' => array('container-inline')),
            );

            $form['c_lat'] = array(
                '#type' => 'textfield',
                '#title' => t('Latitude of map center'),
                '#required' => TRUE,
                '#default_value' => $this->options['c_lat'],
                '#description' => t('Latitude of the center of the map.'),
            );

            $form['c_long'] = array(
                '#type' => 'textfield',
                '#title' => t('Longitude of map center'),
                '#required' => TRUE,
                '#default_value' => $this->options['c_long'],
                '#description' => t('Longitude of the center of the map.'),
            );
            
            $form['map_width'] = array(
                '#type' => 'textfield',
                '#title' => t('Width of the map'),
                '#required' => TRUE,
                '#default_value' => $this->options['map_width']
            );
            
            $form['map_height'] = array(
                '#type' => 'textfield',
                '#title' => t('Height of the map'),
                '#required' => TRUE,
                '#default_value' => $this->options['map_height']
            );

        }

    }
}