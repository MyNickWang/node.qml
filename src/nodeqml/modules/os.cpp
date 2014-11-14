#include "os.h"

#include <QDir>
#include <QHostInfo>

using namespace NodeQml;

OsModule::Data::Data(QV4::ExecutionEngine *v4) :
    QV4::Object::Data(v4)
{
    QV4::Scope scope(v4);
    QV4::ScopedObject self(scope, this);
    QV4::ScopedString s(scope);

#ifdef Q_OS_WIN
    self->defineReadonlyProperty(QStringLiteral("EOL"), (s = v4->newString(QStringLiteral("\r\n"))));
#else
    self->defineReadonlyProperty(QStringLiteral("EOL"), (s = v4->newString(QStringLiteral("\n"))));
#endif

    self->defineDefaultProperty(QStringLiteral("tmpdir"), method_tmpdir);
    self->defineDefaultProperty(QStringLiteral("endianness"), method_endianness);
    self->defineDefaultProperty(QStringLiteral("hostname"), method_hostname);
}


QV4::ReturnedValue OsModule::method_tmpdir(QV4::CallContext *ctx)
{
    return ctx->engine()->newString(QDir::tempPath())->asReturnedValue();
}

QV4::ReturnedValue OsModule::method_endianness(QV4::CallContext *ctx)
{
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    return ctx->engine()->newString(QStringLiteral("LE"))->asReturnedValue();
#else
    return ctx->engine()->newString(QStringLiteral("BE"))->asReturnedValue();
#endif
}

QV4::ReturnedValue OsModule::method_hostname(QV4::CallContext *ctx)
{
    return ctx->engine()->newString(QHostInfo::localHostName())->asReturnedValue();
}
