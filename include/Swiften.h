#pragma once
#include <Swiften/Version.h>
#include <Swiften/AdHoc/OutgoingAdHocCommandSession.h>
#include <Swiften/Avatars/AvatarManager.h>
#include <Swiften/Avatars/AvatarManagerImpl.h>
#include <Swiften/Avatars/AvatarMemoryStorage.h>
#include <Swiften/Avatars/AvatarProvider.h>
#include <Swiften/Avatars/AvatarStorage.h>
#include <Swiften/Avatars/CombinedAvatarProvider.h>
#include <Swiften/Avatars/DummyAvatarManager.h>
#include <Swiften/Avatars/NullAvatarManager.h>
#include <Swiften/Avatars/OfflineAvatarManager.h>
#include <Swiften/Avatars/VCardAvatarManager.h>
#include <Swiften/Avatars/VCardUpdateAvatarManager.h>
#include <Swiften/Base/Algorithm.h>
#include <Swiften/Base/BoostRandomGenerator.h>
#include <Swiften/Base/boost_bsignals.h>
#include <Swiften/Base/ByteArray.h>
#include <Swiften/Base/Concat.h>
#include <Swiften/Base/DateTime.h>
#include <Swiften/Base/Error.h>
#include <Swiften/Base/IDGenerator.h>
#include <Swiften/Base/Paths.h>
#include <Swiften/Base/Platform.h>
#include <Swiften/Base/RandomGenerator.h>
#include <Swiften/Base/SafeAllocator.h>
#include <Swiften/Base/SafeByteArray.h>
#include <Swiften/Base/SafeString.h>
#include <Swiften/Base/SimpleIDGenerator.h>
#include <Swiften/Base/sleep.h>
#include <Swiften/Base/StartStopper.h>
#include <Swiften/Base/String.h>
#include <Swiften/Base/URL.h>
#include <Swiften/Chat/ChatStateNotifier.h>
#include <Swiften/Chat/ChatStateTracker.h>
#include <Swiften/Client/BlockList.h>
#include <Swiften/Client/BlockListImpl.h>
#include <Swiften/Client/Client.h>
#include <Swiften/Client/ClientBlockListManager.h>
#include <Swiften/Client/ClientError.h>
#include <Swiften/Client/ClientOptions.h>
#include <Swiften/Client/ClientSession.h>
#include <Swiften/Client/ClientSessionStanzaChannel.h>
#include <Swiften/Client/ClientXMLTracer.h>
#include <Swiften/Client/CoreClient.h>
#include <Swiften/Client/DummyNickManager.h>
#include <Swiften/Client/DummyStanzaChannel.h>
#include <Swiften/Client/MemoryStorages.h>
#include <Swiften/Client/NickManager.h>
#include <Swiften/Client/NickManagerImpl.h>
#include <Swiften/Client/NickResolver.h>
#include <Swiften/Client/StanzaChannel.h>
#include <Swiften/Client/Storages.h>
#include <Swiften/Client/XMLBeautifier.h>
#include <Swiften/Component/Component.h>
#include <Swiften/Component/ComponentConnector.h>
#include <Swiften/Component/ComponentError.h>
#include <Swiften/Component/ComponentHandshakeGenerator.h>
#include <Swiften/Component/ComponentSession.h>
#include <Swiften/Component/ComponentSessionStanzaChannel.h>
#include <Swiften/Component/ComponentXMLTracer.h>
#include <Swiften/Component/CoreComponent.h>
#include <Swiften/Disco/CapsInfoGenerator.h>
#include <Swiften/Disco/CapsManager.h>
#include <Swiften/Disco/CapsMemoryStorage.h>
#include <Swiften/Disco/CapsProvider.h>
#include <Swiften/Disco/CapsStorage.h>
#include <Swiften/Disco/ClientDiscoManager.h>
#include <Swiften/Disco/DiscoInfoResponder.h>
#include <Swiften/Disco/DiscoServiceWalker.h>
#include <Swiften/Disco/DummyEntityCapsProvider.h>
#include <Swiften/Disco/EntityCapsManager.h>
#include <Swiften/Disco/EntityCapsProvider.h>
#include <Swiften/Disco/GetDiscoInfoRequest.h>
#include <Swiften/Disco/GetDiscoItemsRequest.h>
#include <Swiften/Disco/JIDDiscoInfoResponder.h>
#include <Swiften/Elements/AuthChallenge.h>
#include <Swiften/Elements/AuthFailure.h>
#include <Swiften/Elements/AuthRequest.h>
#include <Swiften/Elements/AuthResponse.h>
#include <Swiften/Elements/AuthSuccess.h>
#include <Swiften/Elements/BlockListPayload.h>
#include <Swiften/Elements/BlockPayload.h>
#include <Swiften/Elements/Body.h>
#include <Swiften/Elements/Bytestreams.h>
#include <Swiften/Elements/CapsInfo.h>
#include <Swiften/Elements/ChatState.h>
#include <Swiften/Elements/Command.h>
#include <Swiften/Elements/ComponentHandshake.h>
#include <Swiften/Elements/Compressed.h>
#include <Swiften/Elements/CompressFailure.h>
#include <Swiften/Elements/CompressRequest.h>
#include <Swiften/Elements/Delay.h>
#include <Swiften/Elements/DeliveryReceipt.h>
#include <Swiften/Elements/DeliveryReceiptRequest.h>
#include <Swiften/Elements/DiscoInfo.h>
#include <Swiften/Elements/DiscoItems.h>
#include <Swiften/Elements/Element.h>
#include <Swiften/Elements/EnableStreamManagement.h>
#include <Swiften/Elements/ErrorPayload.h>
#include <Swiften/Elements/Form.h>
#include <Swiften/Elements/FormField.h>
#include <Swiften/Elements/IBB.h>
#include <Swiften/Elements/InBandRegistrationPayload.h>
#include <Swiften/Elements/IQ.h>
#include <Swiften/Elements/JingleContentPayload.h>
#include <Swiften/Elements/JingleDescription.h>
#include <Swiften/Elements/JingleFileTransferDescription.h>
#include <Swiften/Elements/JingleFileTransferHash.h>
#include <Swiften/Elements/JingleFileTransferReceived.h>
#include <Swiften/Elements/JingleIBBTransportPayload.h>
#include <Swiften/Elements/JinglePayload.h>
#include <Swiften/Elements/JingleS5BTransportPayload.h>
#include <Swiften/Elements/JingleTransportPayload.h>
#include <Swiften/Elements/Last.h>
#include <Swiften/Elements/Message.h>
#include <Swiften/Elements/MUCAdminPayload.h>
#include <Swiften/Elements/MUCDestroyPayload.h>
#include <Swiften/Elements/MUCInvitationPayload.h>
#include <Swiften/Elements/MUCItem.h>
#include <Swiften/Elements/MUCOccupant.h>
#include <Swiften/Elements/MUCOwnerPayload.h>
#include <Swiften/Elements/MUCPayload.h>
#include <Swiften/Elements/MUCUserPayload.h>
#include <Swiften/Elements/Nickname.h>
#include <Swiften/Elements/Payload.h>
#include <Swiften/Elements/Presence.h>
#include <Swiften/Elements/Priority.h>
#include <Swiften/Elements/PrivateStorage.h>
#include <Swiften/Elements/ProtocolHeader.h>
#include <Swiften/Elements/RawXMLPayload.h>
#include <Swiften/Elements/Replace.h>
#include <Swiften/Elements/ResourceBind.h>
#include <Swiften/Elements/RosterItemExchangePayload.h>
#include <Swiften/Elements/RosterItemPayload.h>
#include <Swiften/Elements/RosterPayload.h>
#include <Swiften/Elements/S5BProxyRequest.h>
#include <Swiften/Elements/SearchPayload.h>
#include <Swiften/Elements/SecurityLabel.h>
#include <Swiften/Elements/SecurityLabelsCatalog.h>
#include <Swiften/Elements/SoftwareVersion.h>
#include <Swiften/Elements/Stanza.h>
#include <Swiften/Elements/StanzaAck.h>
#include <Swiften/Elements/StanzaAckRequest.h>
#include <Swiften/Elements/StartSession.h>
#include <Swiften/Elements/StartTLSFailure.h>
#include <Swiften/Elements/StartTLSRequest.h>
#include <Swiften/Elements/Status.h>
#include <Swiften/Elements/StatusShow.h>
#include <Swiften/Elements/Storage.h>
#include <Swiften/Elements/StreamError.h>
#include <Swiften/Elements/StreamFeatures.h>
#include <Swiften/Elements/StreamInitiation.h>
#include <Swiften/Elements/StreamInitiationFileInfo.h>
#include <Swiften/Elements/StreamManagementEnabled.h>
#include <Swiften/Elements/StreamManagementFailed.h>
#include <Swiften/Elements/StreamResume.h>
#include <Swiften/Elements/StreamResumed.h>
#include <Swiften/Elements/StreamType.h>
#include <Swiften/Elements/Subject.h>
#include <Swiften/Elements/TLSProceed.h>
#include <Swiften/Elements/UnblockPayload.h>
#include <Swiften/Elements/UnknownElement.h>
#include <Swiften/Elements/VCard.h>
#include <Swiften/Elements/VCardUpdate.h>
#include <Swiften/Elements/Version.h>
#include <Swiften/Entity/Entity.h>
#include <Swiften/Entity/GenericPayloadPersister.h>
#include <Swiften/Entity/PayloadPersister.h>
#include <Swiften/EventLoop/DummyEventLoop.h>
#include <Swiften/EventLoop/Event.h>
#include <Swiften/EventLoop/EventLoop.h>
#include <Swiften/EventLoop/EventOwner.h>
#include <Swiften/EventLoop/SimpleEventLoop.h>
#include <Swiften/EventLoop/SingleThreadedEventLoop.h>
#include <Swiften/FileTransfer/ByteArrayReadBytestream.h>
#include <Swiften/FileTransfer/ByteArrayWriteBytestream.h>
#include <Swiften/FileTransfer/BytestreamException.h>
#include <Swiften/FileTransfer/BytestreamsRequest.h>
#include <Swiften/FileTransfer/ConnectivityManager.h>
#include <Swiften/FileTransfer/DefaultLocalJingleTransportCandidateGenerator.h>
#include <Swiften/FileTransfer/DefaultLocalJingleTransportCandidateGeneratorFactory.h>
#include <Swiften/FileTransfer/DefaultRemoteJingleTransportCandidateSelector.h>
#include <Swiften/FileTransfer/DefaultRemoteJingleTransportCandidateSelectorFactory.h>
#include <Swiften/FileTransfer/FileReadBytestream.h>
#include <Swiften/FileTransfer/FileTransfer.h>
#include <Swiften/FileTransfer/FileTransferError.h>
#include <Swiften/FileTransfer/FileTransferManager.h>
#include <Swiften/FileTransfer/FileTransferManagerImpl.h>
#include <Swiften/FileTransfer/FileWriteBytestream.h>
#include <Swiften/FileTransfer/IBBReceiveSession.h>
#include <Swiften/FileTransfer/IBBRequest.h>
#include <Swiften/FileTransfer/IBBSendSession.h>
#include <Swiften/FileTransfer/IncomingFileTransfer.h>
#include <Swiften/FileTransfer/IncomingFileTransferManager.h>
#include <Swiften/FileTransfer/IncomingJingleFileTransfer.h>
#include <Swiften/FileTransfer/IncrementalBytestreamHashCalculator.h>
#include <Swiften/FileTransfer/JingleIncomingIBBTransport.h>
#include <Swiften/FileTransfer/JingleTransport.h>
#include <Swiften/FileTransfer/LocalJingleTransportCandidateGenerator.h>
#include <Swiften/FileTransfer/LocalJingleTransportCandidateGeneratorFactory.h>
#include <Swiften/FileTransfer/OutgoingFileTransfer.h>
#include <Swiften/FileTransfer/OutgoingFileTransferManager.h>
#include <Swiften/FileTransfer/OutgoingJingleFileTransfer.h>
#include <Swiften/FileTransfer/OutgoingSIFileTransfer.h>
#include <Swiften/FileTransfer/ReadBytestream.h>
#include <Swiften/FileTransfer/RemoteJingleTransportCandidateSelector.h>
#include <Swiften/FileTransfer/RemoteJingleTransportCandidateSelectorFactory.h>
#include <Swiften/FileTransfer/SOCKS5BytestreamClientSession.h>
#include <Swiften/FileTransfer/SOCKS5BytestreamProxy.h>
#include <Swiften/FileTransfer/SOCKS5BytestreamProxyFinder.h>
#include <Swiften/FileTransfer/SOCKS5BytestreamRegistry.h>
#include <Swiften/FileTransfer/SOCKS5BytestreamServer.h>
#include <Swiften/FileTransfer/SOCKS5BytestreamServerSession.h>
#include <Swiften/FileTransfer/StreamInitiationRequest.h>
#include <Swiften/FileTransfer/WriteBytestream.h>
#include <Swiften/History/HistoryManager.h>
#include <Swiften/History/HistoryMessage.h>
#include <Swiften/JID/JID.h>
#include <Swiften/Jingle/FakeJingleSession.h>
#include <Swiften/Jingle/IncomingJingleSessionHandler.h>
#include <Swiften/Jingle/Jingle.h>
#include <Swiften/Jingle/JingleContentID.h>
#include <Swiften/Jingle/JingleResponder.h>
#include <Swiften/Jingle/JingleSession.h>
#include <Swiften/Jingle/JingleSessionImpl.h>
#include <Swiften/Jingle/JingleSessionManager.h>
#include <Swiften/LinkLocal/IncomingLinkLocalSession.h>
#include <Swiften/LinkLocal/LinkLocalConnector.h>
#include <Swiften/LinkLocal/LinkLocalService.h>
#include <Swiften/LinkLocal/LinkLocalServiceBrowser.h>
#include <Swiften/LinkLocal/LinkLocalServiceInfo.h>
#include <Swiften/LinkLocal/OutgoingLinkLocalSession.h>
#include <Swiften/LinkLocal/DNSSD/DNSSDBrowseQuery.h>
#include <Swiften/LinkLocal/DNSSD/DNSSDQuerier.h>
#include <Swiften/LinkLocal/DNSSD/DNSSDRegisterQuery.h>
#include <Swiften/LinkLocal/DNSSD/DNSSDResolveHostnameQuery.h>
#include <Swiften/LinkLocal/DNSSD/DNSSDResolveServiceQuery.h>
#include <Swiften/LinkLocal/DNSSD/DNSSDServiceID.h>
#include <Swiften/LinkLocal/DNSSD/PlatformDNSSDQuerierFactory.h>
#include <Swiften/LinkLocal/DNSSD/Fake/FakeDNSSDBrowseQuery.h>
#include <Swiften/LinkLocal/DNSSD/Fake/FakeDNSSDQuerier.h>
#include <Swiften/LinkLocal/DNSSD/Fake/FakeDNSSDQuery.h>
#include <Swiften/LinkLocal/DNSSD/Fake/FakeDNSSDRegisterQuery.h>
#include <Swiften/LinkLocal/DNSSD/Fake/FakeDNSSDResolveHostnameQuery.h>
#include <Swiften/LinkLocal/DNSSD/Fake/FakeDNSSDResolveServiceQuery.h>
#include <Swiften/MUC/MUC.h>
#include <Swiften/MUC/MUCBookmark.h>
#include <Swiften/MUC/MUCBookmarkManager.h>
#include <Swiften/MUC/MUCManager.h>
#include <Swiften/MUC/MUCRegistry.h>
#include <Swiften/Network/BoostConnection.h>
#include <Swiften/Network/BoostConnectionFactory.h>
#include <Swiften/Network/BoostConnectionServer.h>
#include <Swiften/Network/BoostConnectionServerFactory.h>
#include <Swiften/Network/BoostIOServiceThread.h>
#include <Swiften/Network/BoostNetworkFactories.h>
#include <Swiften/Network/BoostTimer.h>
#include <Swiften/Network/BoostTimerFactory.h>
#include <Swiften/Network/BOSHConnection.h>
#include <Swiften/Network/BOSHConnectionPool.h>
#include <Swiften/Network/CachingNameOnlyDomainNameResolver.h>
#include <Swiften/Network/ChainedConnector.h>
#include <Swiften/Network/Connection.h>
#include <Swiften/Network/ConnectionFactory.h>
#include <Swiften/Network/ConnectionServer.h>
#include <Swiften/Network/ConnectionServerFactory.h>
#include <Swiften/Network/Connector.h>
#include <Swiften/Network/DomainNameAddressQuery.h>
#include <Swiften/Network/DomainNameResolveError.h>
#include <Swiften/Network/DomainNameResolver.h>
#include <Swiften/Network/DomainNameServiceQuery.h>
#include <Swiften/Network/DummyConnection.h>
#include <Swiften/Network/DummyConnectionFactory.h>
#include <Swiften/Network/DummyTimerFactory.h>
#include <Swiften/Network/EnvironmentProxyProvider.h>
#include <Swiften/Network/FakeConnection.h>
#include <Swiften/Network/HostAddress.h>
#include <Swiften/Network/HostAddressPort.h>
#include <Swiften/Network/HTTPConnectProxiedConnection.h>
#include <Swiften/Network/HTTPConnectProxiedConnectionFactory.h>
#include <Swiften/Network/NATPortMapping.h>
#include <Swiften/Network/NATTraversalForwardPortRequest.h>
#include <Swiften/Network/NATTraversalGetPublicIPRequest.h>
#include <Swiften/Network/NATTraversalInterface.h>
#include <Swiften/Network/NATTraversalRemovePortForwardingRequest.h>
#include <Swiften/Network/NATTraverser.h>
#include <Swiften/Network/NetworkEnvironment.h>
#include <Swiften/Network/NetworkFactories.h>
#include <Swiften/Network/NetworkInterface.h>
#include <Swiften/Network/NullNATTraversalInterface.h>
#include <Swiften/Network/NullNATTraverser.h>
#include <Swiften/Network/NullProxyProvider.h>
#include <Swiften/Network/PlatformDomainNameAddressQuery.h>
#include <Swiften/Network/PlatformDomainNameQuery.h>
#include <Swiften/Network/PlatformDomainNameResolver.h>
#include <Swiften/Network/PlatformDomainNameServiceQuery.h>
#include <Swiften/Network/PlatformNATTraversalWorker.h>
#include <Swiften/Network/PlatformNetworkEnvironment.h>
#include <Swiften/Network/PlatformProxyProvider.h>
#include <Swiften/Network/ProxyProvider.h>
#include <Swiften/Network/SOCKS5ProxiedConnection.h>
#include <Swiften/Network/SOCKS5ProxiedConnectionFactory.h>
#include <Swiften/Network/StaticDomainNameResolver.h>
#include <Swiften/Network/Timer.h>
#include <Swiften/Network/TimerFactory.h>
#include <Swiften/Network/TLSConnection.h>
#include <Swiften/Network/TLSConnectionFactory.h>
#include <Swiften/Network/UnixNetworkEnvironment.h>
#include <Swiften/Network/UnixProxyProvider.h>
#include <Swiften/Parser/Attribute.h>
#include <Swiften/Parser/AttributeMap.h>
#include <Swiften/Parser/AuthChallengeParser.h>
#include <Swiften/Parser/AuthFailureParser.h>
#include <Swiften/Parser/AuthRequestParser.h>
#include <Swiften/Parser/AuthResponseParser.h>
#include <Swiften/Parser/AuthSuccessParser.h>
#include <Swiften/Parser/BOSHBodyExtractor.h>
#include <Swiften/Parser/ComponentHandshakeParser.h>
#include <Swiften/Parser/CompressedParser.h>
#include <Swiften/Parser/CompressFailureParser.h>
#include <Swiften/Parser/CompressParser.h>
#include <Swiften/Parser/ElementParser.h>
#include <Swiften/Parser/EnableStreamManagementParser.h>
#include <Swiften/Parser/GenericElementParser.h>
#include <Swiften/Parser/GenericPayloadParser.h>
#include <Swiften/Parser/GenericPayloadParserFactory.h>
#include <Swiften/Parser/GenericPayloadTreeParser.h>
#include <Swiften/Parser/GenericStanzaParser.h>
#include <Swiften/Parser/IQParser.h>
#include <Swiften/Parser/MessageParser.h>
#include <Swiften/Parser/PayloadParser.h>
#include <Swiften/Parser/PayloadParserFactory.h>
#include <Swiften/Parser/PayloadParserFactoryCollection.h>
#include <Swiften/Parser/PlatformXMLParserFactory.h>
#include <Swiften/Parser/PresenceParser.h>
#include <Swiften/Parser/SerializingParser.h>
#include <Swiften/Parser/StanzaAckParser.h>
#include <Swiften/Parser/StanzaAckRequestParser.h>
#include <Swiften/Parser/StanzaParser.h>
#include <Swiften/Parser/StartTLSFailureParser.h>
#include <Swiften/Parser/StartTLSParser.h>
#include <Swiften/Parser/StreamErrorParser.h>
#include <Swiften/Parser/StreamFeaturesParser.h>
#include <Swiften/Parser/StreamManagementEnabledParser.h>
#include <Swiften/Parser/StreamManagementFailedParser.h>
#include <Swiften/Parser/StreamResumedParser.h>
#include <Swiften/Parser/StreamResumeParser.h>
#include <Swiften/Parser/TLSProceedParser.h>
#include <Swiften/Parser/UnknownElementParser.h>
#include <Swiften/Parser/UnknownPayloadParser.h>
#include <Swiften/Parser/XMLParser.h>
#include <Swiften/Parser/XMLParserClient.h>
#include <Swiften/Parser/XMLParserFactory.h>
#include <Swiften/Parser/XMPPParser.h>
#include <Swiften/Parser/XMPPParserClient.h>
#include <Swiften/Parser/PayloadParsers/BlockParser.h>
#include <Swiften/Parser/PayloadParsers/BodyParser.h>
#include <Swiften/Parser/PayloadParsers/BytestreamsParser.h>
#include <Swiften/Parser/PayloadParsers/CapsInfoParser.h>
#include <Swiften/Parser/PayloadParsers/ChatStateParser.h>
#include <Swiften/Parser/PayloadParsers/ChatStateParserFactory.h>
#include <Swiften/Parser/PayloadParsers/CommandParser.h>
#include <Swiften/Parser/PayloadParsers/DelayParser.h>
#include <Swiften/Parser/PayloadParsers/DeliveryReceiptParser.h>
#include <Swiften/Parser/PayloadParsers/DeliveryReceiptParserFactory.h>
#include <Swiften/Parser/PayloadParsers/DeliveryReceiptRequestParser.h>
#include <Swiften/Parser/PayloadParsers/DeliveryReceiptRequestParserFactory.h>
#include <Swiften/Parser/PayloadParsers/DiscoInfoParser.h>
#include <Swiften/Parser/PayloadParsers/DiscoItemsParser.h>
#include <Swiften/Parser/PayloadParsers/ErrorParser.h>
#include <Swiften/Parser/PayloadParsers/ErrorParserFactory.h>
#include <Swiften/Parser/PayloadParsers/FormParser.h>
#include <Swiften/Parser/PayloadParsers/FormParserFactory.h>
#include <Swiften/Parser/PayloadParsers/FullPayloadParserFactoryCollection.h>
#include <Swiften/Parser/PayloadParsers/IBBParser.h>
#include <Swiften/Parser/PayloadParsers/InBandRegistrationPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/JingleContentPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/JingleContentPayloadParserFactory.h>
#include <Swiften/Parser/PayloadParsers/JingleFileTransferDescriptionParser.h>
#include <Swiften/Parser/PayloadParsers/JingleFileTransferDescriptionParserFactory.h>
#include <Swiften/Parser/PayloadParsers/JingleFileTransferHashParser.h>
#include <Swiften/Parser/PayloadParsers/JingleFileTransferReceivedParser.h>
#include <Swiften/Parser/PayloadParsers/JingleIBBTransportMethodPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/JingleParser.h>
#include <Swiften/Parser/PayloadParsers/JingleParserFactory.h>
#include <Swiften/Parser/PayloadParsers/JingleReasonParser.h>
#include <Swiften/Parser/PayloadParsers/JingleS5BTransportMethodPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/LastParser.h>
#include <Swiften/Parser/PayloadParsers/MUCAdminPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/MUCDestroyPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/MUCInvitationPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/MUCItemParser.h>
#include <Swiften/Parser/PayloadParsers/MUCOwnerPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/MUCOwnerPayloadParserFactory.h>
#include <Swiften/Parser/PayloadParsers/MUCUserPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/MUCUserPayloadParserFactory.h>
#include <Swiften/Parser/PayloadParsers/NicknameParser.h>
#include <Swiften/Parser/PayloadParsers/PriorityParser.h>
#include <Swiften/Parser/PayloadParsers/PrivateStorageParser.h>
#include <Swiften/Parser/PayloadParsers/PrivateStorageParserFactory.h>
#include <Swiften/Parser/PayloadParsers/RawXMLPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/RawXMLPayloadParserFactory.h>
#include <Swiften/Parser/PayloadParsers/ReplaceParser.h>
#include <Swiften/Parser/PayloadParsers/ResourceBindParser.h>
#include <Swiften/Parser/PayloadParsers/RosterItemExchangeParser.h>
#include <Swiften/Parser/PayloadParsers/RosterParser.h>
#include <Swiften/Parser/PayloadParsers/S5BProxyRequestParser.h>
#include <Swiften/Parser/PayloadParsers/SearchPayloadParser.h>
#include <Swiften/Parser/PayloadParsers/SecurityLabelParser.h>
#include <Swiften/Parser/PayloadParsers/SecurityLabelParserFactory.h>
#include <Swiften/Parser/PayloadParsers/SecurityLabelsCatalogParser.h>
#include <Swiften/Parser/PayloadParsers/SoftwareVersionParser.h>
#include <Swiften/Parser/PayloadParsers/StartSessionParser.h>
#include <Swiften/Parser/PayloadParsers/StatusParser.h>
#include <Swiften/Parser/PayloadParsers/StatusShowParser.h>
#include <Swiften/Parser/PayloadParsers/StorageParser.h>
#include <Swiften/Parser/PayloadParsers/StreamInitiationFileInfoParser.h>
#include <Swiften/Parser/PayloadParsers/StreamInitiationParser.h>
#include <Swiften/Parser/PayloadParsers/SubjectParser.h>
#include <Swiften/Parser/PayloadParsers/VCardParser.h>
#include <Swiften/Parser/PayloadParsers/VCardUpdateParser.h>
#include <Swiften/Parser/Tree/NullParserElement.h>
#include <Swiften/Parser/Tree/ParserElement.h>
#include <Swiften/Parser/Tree/TreeReparser.h>
#include <Swiften/Presence/DirectedPresenceSender.h>
#include <Swiften/Presence/PayloadAddingPresenceSender.h>
#include <Swiften/Presence/PresenceOracle.h>
#include <Swiften/Presence/PresenceSender.h>
#include <Swiften/Presence/StanzaChannelPresenceSender.h>
#include <Swiften/Presence/SubscriptionManager.h>
#include <Swiften/Queries/DummyIQChannel.h>
#include <Swiften/Queries/GenericRequest.h>
#include <Swiften/Queries/GetResponder.h>
#include <Swiften/Queries/IQChannel.h>
#include <Swiften/Queries/IQHandler.h>
#include <Swiften/Queries/IQRouter.h>
#include <Swiften/Queries/RawRequest.h>
#include <Swiften/Queries/Request.h>
#include <Swiften/Queries/Responder.h>
#include <Swiften/Queries/SetResponder.h>
#include <Swiften/Queries/Requests/GetInBandRegistrationFormRequest.h>
#include <Swiften/Queries/Requests/GetPrivateStorageRequest.h>
#include <Swiften/Queries/Requests/GetSecurityLabelsCatalogRequest.h>
#include <Swiften/Queries/Requests/GetSoftwareVersionRequest.h>
#include <Swiften/Queries/Requests/SetPrivateStorageRequest.h>
#include <Swiften/Queries/Requests/SubmitInBandRegistrationFormRequest.h>
#include <Swiften/Queries/Responders/SoftwareVersionResponder.h>
#include <Swiften/Roster/GetRosterRequest.h>
#include <Swiften/Roster/RosterMemoryStorage.h>
#include <Swiften/Roster/RosterPushResponder.h>
#include <Swiften/Roster/RosterStorage.h>
#include <Swiften/Roster/SetRosterRequest.h>
#include <Swiften/Roster/XMPPRoster.h>
#include <Swiften/Roster/XMPPRosterController.h>
#include <Swiften/Roster/XMPPRosterImpl.h>
#include <Swiften/Roster/XMPPRosterItem.h>
#include <Swiften/SASL/ClientAuthenticator.h>
#include <Swiften/SASL/DIGESTMD5ClientAuthenticator.h>
#include <Swiften/SASL/DIGESTMD5Properties.h>
#include <Swiften/SASL/PLAINClientAuthenticator.h>
#include <Swiften/SASL/PLAINMessage.h>
#include <Swiften/SASL/SCRAMSHA1ClientAuthenticator.h>
#include <Swiften/Serializer/AuthChallengeSerializer.h>
#include <Swiften/Serializer/AuthFailureSerializer.h>
#include <Swiften/Serializer/AuthRequestSerializer.h>
#include <Swiften/Serializer/AuthResponseSerializer.h>
#include <Swiften/Serializer/AuthSuccessSerializer.h>
#include <Swiften/Serializer/ComponentHandshakeSerializer.h>
#include <Swiften/Serializer/CompressFailureSerializer.h>
#include <Swiften/Serializer/CompressRequestSerializer.h>
#include <Swiften/Serializer/ElementSerializer.h>
#include <Swiften/Serializer/EnableStreamManagementSerializer.h>
#include <Swiften/Serializer/GenericElementSerializer.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Serializer/GenericStanzaSerializer.h>
#include <Swiften/Serializer/IQSerializer.h>
#include <Swiften/Serializer/MessageSerializer.h>
#include <Swiften/Serializer/PayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializerCollection.h>
#include <Swiften/Serializer/PresenceSerializer.h>
#include <Swiften/Serializer/StanzaAckRequestSerializer.h>
#include <Swiften/Serializer/StanzaAckSerializer.h>
#include <Swiften/Serializer/StanzaSerializer.h>
#include <Swiften/Serializer/StartTLSFailureSerializer.h>
#include <Swiften/Serializer/StartTLSRequestSerializer.h>
#include <Swiften/Serializer/StreamErrorSerializer.h>
#include <Swiften/Serializer/StreamFeaturesSerializer.h>
#include <Swiften/Serializer/StreamManagementEnabledSerializer.h>
#include <Swiften/Serializer/StreamManagementFailedSerializer.h>
#include <Swiften/Serializer/StreamResumedSerializer.h>
#include <Swiften/Serializer/StreamResumeSerializer.h>
#include <Swiften/Serializer/TLSProceedSerializer.h>
#include <Swiften/Serializer/XMPPSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/BlockSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/BodySerializer.h>
#include <Swiften/Serializer/PayloadSerializers/BytestreamsSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/CapsInfoSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/ChatStateSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/CommandSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/DelaySerializer.h>
#include <Swiften/Serializer/PayloadSerializers/DeliveryReceiptRequestSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/DeliveryReceiptSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/DiscoInfoSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/DiscoItemsSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/ErrorSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/FormSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/FullPayloadSerializerCollection.h>
#include <Swiften/Serializer/PayloadSerializers/IBBSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/InBandRegistrationPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/JingleContentPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/JingleFileTransferDescriptionSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/JingleFileTransferHashSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/JingleFileTransferReceivedSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/JingleIBBTransportPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/JinglePayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/JingleS5BTransportPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/LastSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/MUCAdminPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/MUCDestroyPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/MUCInvitationPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/MUCItemSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/MUCOwnerPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/MUCPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/MUCUserPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/NicknameSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/PrioritySerializer.h>
#include <Swiften/Serializer/PayloadSerializers/PrivateStorageSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/RawXMLPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/ReplaceSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/ResourceBindSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/RosterItemExchangeSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/RosterSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/S5BProxyRequestSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/SearchPayloadSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/SecurityLabelsCatalogSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/SecurityLabelSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/SoftwareVersionSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/StartSessionSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/StatusSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/StatusShowSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/StorageSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/StreamInitiationFileInfoSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/StreamInitiationSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/SubjectSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/VCardSerializer.h>
#include <Swiften/Serializer/PayloadSerializers/VCardUpdateSerializer.h>
#include <Swiften/Serializer/XML/XMLElement.h>
#include <Swiften/Serializer/XML/XMLNode.h>
#include <Swiften/Serializer/XML/XMLRawTextNode.h>
#include <Swiften/Serializer/XML/XMLTextNode.h>
#include <Swiften/Session/BasicSessionStream.h>
#include <Swiften/Session/BOSHSessionStream.h>
#include <Swiften/Session/Session.h>
#include <Swiften/Session/SessionStream.h>
#include <Swiften/Session/SessionTracer.h>
#include <Swiften/StreamManagement/StanzaAckRequester.h>
#include <Swiften/StreamManagement/StanzaAckResponder.h>
#include <Swiften/StreamStack/ConnectionLayer.h>
#include <Swiften/StreamStack/HighLayer.h>
#include <Swiften/StreamStack/LowLayer.h>
#include <Swiften/StreamStack/StreamLayer.h>
#include <Swiften/StreamStack/StreamStack.h>
#include <Swiften/StreamStack/TLSLayer.h>
#include <Swiften/StreamStack/WhitespacePingLayer.h>
#include <Swiften/StreamStack/XMPPLayer.h>
#include <Swiften/StringCodecs/Base64.h>
#include <Swiften/StringCodecs/Hexify.h>
#include <Swiften/StringCodecs/HMAC.h>
#include <Swiften/StringCodecs/HMAC_SHA1.h>
#include <Swiften/StringCodecs/HMAC_SHA256.h>
#include <Swiften/StringCodecs/MD5.h>
#include <Swiften/StringCodecs/PBKDF2.h>
#include <Swiften/StringCodecs/SHA1.h>
#include <Swiften/StringCodecs/SHA256.h>
#include <Swiften/TLS/BlindCertificateTrustChecker.h>
#include <Swiften/TLS/Certificate.h>
#include <Swiften/TLS/CertificateFactory.h>
#include <Swiften/TLS/CertificateTrustChecker.h>
#include <Swiften/TLS/CertificateVerificationError.h>
#include <Swiften/TLS/CertificateWithKey.h>
#include <Swiften/TLS/PKCS12Certificate.h>
#include <Swiften/TLS/PlatformTLSFactories.h>
#include <Swiften/TLS/ServerIdentityVerifier.h>
#include <Swiften/TLS/SimpleCertificate.h>
#include <Swiften/TLS/TLSContext.h>
#include <Swiften/TLS/TLSContextFactory.h>
#include <Swiften/TLS/TLSError.h>
#include <Swiften/VCards/GetVCardRequest.h>
#include <Swiften/VCards/SetVCardRequest.h>
#include <Swiften/VCards/VCardManager.h>
#include <Swiften/VCards/VCardMemoryStorage.h>
#include <Swiften/VCards/VCardStorage.h>
