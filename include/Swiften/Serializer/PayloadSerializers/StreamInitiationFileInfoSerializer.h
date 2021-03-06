/*
 * Copyright (c) 2011 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */


#pragma once

#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/StreamInitiationFileInfo.h>

#include <Swiften/Serializer/XML/XMLElement.h>

namespace Swift {
	class PayloadSerializerCollection;

	class StreamInitiationFileInfoSerializer : public GenericPayloadSerializer<StreamInitiationFileInfo> {
		public:
			StreamInitiationFileInfoSerializer();

			virtual std::string serializePayload(boost::shared_ptr<StreamInitiationFileInfo>)  const;
	};
}
