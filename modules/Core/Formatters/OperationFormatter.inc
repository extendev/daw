<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Modules\Core\Formatters;

class OperationFormatter extends \Daw\Core\Formatter\Formatter {

	/**
	 * Return TRUE if formatter supports given object and possibly given format
	 *
	 * Enter description here ...
	 * @param mixed $object
	 * @param string $format
	 */
	public function isFormatterFor($object, $format = null) {
		return $object instanceof \Daw\Core\Object\Operation;
	}

	public function render($object, $format) {

	}
}