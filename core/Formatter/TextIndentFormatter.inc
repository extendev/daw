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
 * TextIndent Default Formatter
 * This formatter supports any type of objects
 *
 * @package Daw
 * @subpackage Formatters
 * @author Axel Tessier <axel.tessier@extendev.net>
 * @version $Id: Event.inc 112 2003-08-22 06:22:40Z  $
 */
class TextIndentFormatter extends \Daw\Core\Formatter\Formatter {

    /**
     * Return true if formatter supports given object and possibly given format
     *
     * This formatter accepts any object provided that requested format is TextIndent
     *
     * @param object $object object to render
     * @param DawCoreFormatter\Format $format format to be used for rendering
     * @return boolean
     */
    public function isFormatterFor($object, $format = null) {
        return $format === 'TextIndent';
    }

    /**
     * Render object passed as first argument.
     *
     * Format to be used for renderring the object is passed as second argument
     * in case the formatter supports multiple formats
     *
     * @param object $object object to render
     * @param DawCoreFormatter\Format $format format to be used for rendering
     * @return
     */
    public function render($object, $format) {
    	$contents = null;
		if (is_array($object)) {
			$indentLevel = $this->context->indentLevel;
			$this->context->indentLevel = ($indentLevel === null) ? 0 : ($indentLevel + 1);
			$contents .= "\n";
			foreach ($object as $label => $item) {
				$contents .= str_repeat('  ', $this->context->indentLevel) . "$label:" . $this->core->render($item, $format) . "\n";
			}
			$this->context->indentLevel = $indentLevel;
		} else {
			$contents = $this->core->yaml->dump($object, 2, $this->context->get('indentLevel', 1));
		}

		return $contents === 'null' ? '' : $contents;
    }
}
