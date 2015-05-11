#ifndef CODE_CONTROLLER_H
#define CODE_CONTROLLER_H

#include <string>
#include <map>

#include "component/controller/helper/SnippetMerger.h"
#include "component/controller/Controller.h"
#include "component/view/CodeView.h"
#include "utility/messaging/MessageListener.h"
#include "utility/messaging/type/MessageActivateTokenLocation.h"
#include "utility/messaging/type/MessageActivateTokens.h"
#include "utility/messaging/type/MessageFinishedParsing.h"
#include "utility/messaging/type/MessageRefresh.h"
#include "utility/messaging/type/MessageShowFile.h"
#include "utility/types.h"

class StorageAccess;
class TokenLocationFile;

class CodeController
	: public Controller
	, public MessageListener<MessageActivateTokenLocation>
	, public MessageListener<MessageActivateTokens>
	, public MessageListener<MessageFinishedParsing>
	, public MessageListener<MessageRefresh>
	, public MessageListener<MessageShowFile>
{
public:
	CodeController(StorageAccess* storageAccess);
	~CodeController();

private:
	static const uint s_lineRadius;

	virtual void handleMessage(MessageActivateTokenLocation* message);
	virtual void handleMessage(MessageActivateTokens* message);
	virtual void handleMessage(MessageFinishedParsing* message);
	virtual void handleMessage(MessageRefresh* message);
	virtual void handleMessage(MessageShowFile* message);

	CodeView* getView();

	std::vector<CodeView::CodeSnippetParams> getSnippetsForActiveTokenIds(
		const std::vector<Id>& ids, Id declarationId) const;
	std::vector<CodeView::CodeSnippetParams> getSnippetsForFile(std::shared_ptr<TokenLocationFile> file) const;
	std::shared_ptr<SnippetMerger> buildMergerHierarchy(
		TokenLocation* location, SnippetMerger& fileScopedMerger, std::map<int, std::shared_ptr<SnippetMerger>>& mergers) const;

	StorageAccess* m_storageAccess;
};

#endif // CODE_CONTROLLER_H
