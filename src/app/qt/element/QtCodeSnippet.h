#ifndef QT_CODE_SNIPPET_H
#define QT_CODE_SNIPPET_H

#include <vector>
#include <memory>

#include "utility/types.h"
#include "qt/element/QtCodeArea.h"

class QtCodeFile;
class QWidget;
class TokenLocationFile;

class QtCodeSnippet: public QWidget
{
	Q_OBJECT

public:

	QtCodeSnippet(
		uint startLineNumber,
		const std::string& title,
		const std::string& code,
		std::shared_ptr<TokenLocationFile> locationFile,
		QtCodeFile* parent
	);
	virtual ~QtCodeSnippet();

	void addMaximizeButton();

	int lineNumberDigits() const;

	void updateLineNumberAreaWidthForDigits(int digits);
	void update();

private:
	QtCodeFile* m_parent; // need this?
	QPushButton* m_title;
	std::shared_ptr<QtCodeArea> m_codeArea;
};

#endif // QT_CODE_SNIPPET_H
