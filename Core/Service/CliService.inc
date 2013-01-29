<?php

/*
 * This file is part of the Daw package.
 *
 * (c) Axel Tessier <axel.tessier@extendev.net>
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 */

namespace Daw\Core\Service;

use \Daw\Core\Service\Service
use \Daw\Core\Service\Cli\CliServiceRequest
use \Daw\Core\Service\Cli\CliServiceResponse

/**
* Command Line Service
*
* This is the long description for a DocBlock. This text may contain
* multiple lines and even some _markdown_.
*
* * Markdown style lists function too
* * Just try this out once
*
* The section after the long description contains the tags; which provide
* structured meta-data concerning the given element.
*
* @author  Mike van Riel <mike.vanriel@naenius.com>
* @since 1.0
* @version $Id$
*/
class CliService extends Service {

	const RESPONSE_FORMAT =  'TextIndent';

	public function getRequest() {
		return new CliServiceRequest();
	}

	public function buildResponse() {
		return new CliServiceResponse();
	}

	public function getResponseFormat() {
		return self::RESPONSE_FORMAT;
	}
}
