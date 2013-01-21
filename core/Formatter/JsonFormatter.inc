<?php

/**
 * Application Formatters
 *
 * @package Daw
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */

namespace Daw\Core\Formatter;

/**
 * JSON Default Formatter
 *
 * This formatter supports any type of objects
 *
 * @package Daw
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class JsonFormatter extends \Daw\Core\Formatter\Formatter {

    /**
     * Return true if formatter supports given object and possibly given format
     *
     * This formatter accepts any object provided that requested format is Json
     *
     * @param object $object object to render
     * @param Daw\Core\Formatter\Format $format format to be used for rendering
     * @return boolean
     */
    public function isFormatterFor($object, $format = null) {
        return $format === 'Json';
    }

    /**
     * Render object passed as first argument.
     *
     * Format to be used for renderring the object is passed as second argument
     * in case the formatter supports multiple formats
     *
     * @param object $object object to render
     * @param Daw\Core\Formatter\Format $format format to be used for rendering
     * @return
     */
    public function render($object, $format) {
    	$contents = null;

    	if (is_array($object)) {

    		// Check if array, otherwise use object structure
    		$is_object = false;
    		$idx = 0;
    		$arr = array();
    		foreach ($object as $label => $item) {
    			if (!$is_object
    				&& (!is_numeric($label)
    					|| $label != $idx)) {
    				$is_object = true;
    			}

    			$arr[$label] = $this->core->render($item, $format);

    			$idx++;
    		}

    		if ($is_object && count($arr)) {
    			$arrStr = array();
    			foreach ($arr as $label => $value) {
    				$arrStr[] = "\"$label\": " . $value;
    			}
    			$contents = '{' . join(', ', $arrStr) . '}';
    		} else {
    			$contents = '[' . join(', ', array_values($arr)) . ']';
    		}

    	} else {
    		$contents = json_encode($object);
    	}

    	return $contents;
    }
}
