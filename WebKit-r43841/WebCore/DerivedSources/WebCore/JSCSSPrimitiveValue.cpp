/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#include "JSCSSPrimitiveValue.h"

#include <wtf/GetPtr.h>

#include "CSSPrimitiveValue.h"
#include "Counter.h"
#include "JSCounter.h"
#include "JSRGBColor.h"
#include "JSRect.h"
#include "KURL.h"
#include "Rect.h"

#include <runtime/Error.h>
#include <runtime/JSNumberCell.h>
#include <runtime/JSString.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSCSSPrimitiveValue);

/* Hash table */

static const HashTableValue JSCSSPrimitiveValueTableValues[3] =
{
    { "primitiveType", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValuePrimitiveType, (intptr_t)0 },
    { "constructor", DontEnum|ReadOnly, (intptr_t)jsCSSPrimitiveValueConstructor, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSPrimitiveValueTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 1, JSCSSPrimitiveValueTableValues, 0 };
#else
    { 4, 3, JSCSSPrimitiveValueTableValues, 0 };
#endif

/* Hash table for constructor */

static const HashTableValue JSCSSPrimitiveValueConstructorTableValues[27] =
{
    { "CSS_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_UNKNOWN, (intptr_t)0 },
    { "CSS_NUMBER", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_NUMBER, (intptr_t)0 },
    { "CSS_PERCENTAGE", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PERCENTAGE, (intptr_t)0 },
    { "CSS_EMS", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_EMS, (intptr_t)0 },
    { "CSS_EXS", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_EXS, (intptr_t)0 },
    { "CSS_PX", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PX, (intptr_t)0 },
    { "CSS_CM", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_CM, (intptr_t)0 },
    { "CSS_MM", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_MM, (intptr_t)0 },
    { "CSS_IN", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_IN, (intptr_t)0 },
    { "CSS_PT", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PT, (intptr_t)0 },
    { "CSS_PC", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PC, (intptr_t)0 },
    { "CSS_DEG", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_DEG, (intptr_t)0 },
    { "CSS_RAD", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_RAD, (intptr_t)0 },
    { "CSS_GRAD", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_GRAD, (intptr_t)0 },
    { "CSS_MS", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_MS, (intptr_t)0 },
    { "CSS_S", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_S, (intptr_t)0 },
    { "CSS_HZ", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_HZ, (intptr_t)0 },
    { "CSS_KHZ", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_KHZ, (intptr_t)0 },
    { "CSS_DIMENSION", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_DIMENSION, (intptr_t)0 },
    { "CSS_STRING", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_STRING, (intptr_t)0 },
    { "CSS_URI", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_URI, (intptr_t)0 },
    { "CSS_IDENT", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_IDENT, (intptr_t)0 },
    { "CSS_ATTR", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_ATTR, (intptr_t)0 },
    { "CSS_COUNTER", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_COUNTER, (intptr_t)0 },
    { "CSS_RECT", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_RECT, (intptr_t)0 },
    { "CSS_RGBCOLOR", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_RGBCOLOR, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSPrimitiveValueConstructorTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 8191, JSCSSPrimitiveValueConstructorTableValues, 0 };
#else
    { 69, 63, JSCSSPrimitiveValueConstructorTableValues, 0 };
#endif

class JSCSSPrimitiveValueConstructor : public DOMObject {
public:
    JSCSSPrimitiveValueConstructor(ExecState* exec)
        : DOMObject(JSCSSPrimitiveValueConstructor::createStructure(exec->lexicalGlobalObject()->objectPrototype()))
    {
        putDirect(exec->propertyNames().prototype, JSCSSPrimitiveValuePrototype::self(exec, exec->lexicalGlobalObject()), None);
    }
    virtual bool getOwnPropertySlot(ExecState*, const Identifier&, PropertySlot&);
    virtual const ClassInfo* classInfo() const { return &s_info; }
    static const ClassInfo s_info;

    static PassRefPtr<Structure> createStructure(JSValue proto) 
    { 
        return Structure::create(proto, TypeInfo(ObjectType, ImplementsHasInstance)); 
    }
};

const ClassInfo JSCSSPrimitiveValueConstructor::s_info = { "CSSPrimitiveValueConstructor", 0, &JSCSSPrimitiveValueConstructorTable, 0 };

bool JSCSSPrimitiveValueConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCSSPrimitiveValueConstructor, DOMObject>(exec, &JSCSSPrimitiveValueConstructorTable, this, propertyName, slot);
}

/* Hash table for prototype */

static const HashTableValue JSCSSPrimitiveValuePrototypeTableValues[34] =
{
    { "CSS_UNKNOWN", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_UNKNOWN, (intptr_t)0 },
    { "CSS_NUMBER", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_NUMBER, (intptr_t)0 },
    { "CSS_PERCENTAGE", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PERCENTAGE, (intptr_t)0 },
    { "CSS_EMS", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_EMS, (intptr_t)0 },
    { "CSS_EXS", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_EXS, (intptr_t)0 },
    { "CSS_PX", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PX, (intptr_t)0 },
    { "CSS_CM", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_CM, (intptr_t)0 },
    { "CSS_MM", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_MM, (intptr_t)0 },
    { "CSS_IN", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_IN, (intptr_t)0 },
    { "CSS_PT", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PT, (intptr_t)0 },
    { "CSS_PC", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_PC, (intptr_t)0 },
    { "CSS_DEG", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_DEG, (intptr_t)0 },
    { "CSS_RAD", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_RAD, (intptr_t)0 },
    { "CSS_GRAD", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_GRAD, (intptr_t)0 },
    { "CSS_MS", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_MS, (intptr_t)0 },
    { "CSS_S", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_S, (intptr_t)0 },
    { "CSS_HZ", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_HZ, (intptr_t)0 },
    { "CSS_KHZ", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_KHZ, (intptr_t)0 },
    { "CSS_DIMENSION", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_DIMENSION, (intptr_t)0 },
    { "CSS_STRING", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_STRING, (intptr_t)0 },
    { "CSS_URI", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_URI, (intptr_t)0 },
    { "CSS_IDENT", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_IDENT, (intptr_t)0 },
    { "CSS_ATTR", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_ATTR, (intptr_t)0 },
    { "CSS_COUNTER", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_COUNTER, (intptr_t)0 },
    { "CSS_RECT", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_RECT, (intptr_t)0 },
    { "CSS_RGBCOLOR", DontDelete|ReadOnly, (intptr_t)jsCSSPrimitiveValueCSS_RGBCOLOR, (intptr_t)0 },
    { "setFloatValue", DontDelete|Function, (intptr_t)jsCSSPrimitiveValuePrototypeFunctionSetFloatValue, (intptr_t)2 },
    { "getFloatValue", DontDelete|Function, (intptr_t)jsCSSPrimitiveValuePrototypeFunctionGetFloatValue, (intptr_t)1 },
    { "setStringValue", DontDelete|Function, (intptr_t)jsCSSPrimitiveValuePrototypeFunctionSetStringValue, (intptr_t)2 },
    { "getStringValue", DontDelete|Function, (intptr_t)jsCSSPrimitiveValuePrototypeFunctionGetStringValue, (intptr_t)0 },
    { "getCounterValue", DontDelete|Function, (intptr_t)jsCSSPrimitiveValuePrototypeFunctionGetCounterValue, (intptr_t)0 },
    { "getRectValue", DontDelete|Function, (intptr_t)jsCSSPrimitiveValuePrototypeFunctionGetRectValue, (intptr_t)0 },
    { "getRGBColorValue", DontDelete|Function, (intptr_t)jsCSSPrimitiveValuePrototypeFunctionGetRGBColorValue, (intptr_t)0 },
    { 0, 0, 0, 0 }
};

static const HashTable JSCSSPrimitiveValuePrototypeTable =
#if ENABLE(PERFECT_HASH_SIZE)
    { 8191, JSCSSPrimitiveValuePrototypeTableValues, 0 };
#else
    { 132, 127, JSCSSPrimitiveValuePrototypeTableValues, 0 };
#endif

const ClassInfo JSCSSPrimitiveValuePrototype::s_info = { "CSSPrimitiveValuePrototype", 0, &JSCSSPrimitiveValuePrototypeTable, 0 };

JSObject* JSCSSPrimitiveValuePrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSCSSPrimitiveValue>(exec, globalObject);
}

bool JSCSSPrimitiveValuePrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticPropertySlot<JSCSSPrimitiveValuePrototype, JSObject>(exec, &JSCSSPrimitiveValuePrototypeTable, this, propertyName, slot);
}

const ClassInfo JSCSSPrimitiveValue::s_info = { "CSSPrimitiveValue", &JSCSSValue::s_info, &JSCSSPrimitiveValueTable, 0 };

JSCSSPrimitiveValue::JSCSSPrimitiveValue(PassRefPtr<Structure> structure, PassRefPtr<CSSPrimitiveValue> impl)
    : JSCSSValue(structure, impl)
{
}

JSObject* JSCSSPrimitiveValue::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSCSSPrimitiveValuePrototype(JSCSSPrimitiveValuePrototype::createStructure(JSCSSValuePrototype::self(exec, globalObject)));
}

bool JSCSSPrimitiveValue::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCSSPrimitiveValue, Base>(exec, &JSCSSPrimitiveValueTable, this, propertyName, slot);
}

JSValue jsCSSPrimitiveValuePrimitiveType(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    UNUSED_PARAM(exec);
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(static_cast<JSCSSPrimitiveValue*>(asObject(slot.slotBase()))->impl());
    return jsNumber(exec, imp->primitiveType());
}

JSValue jsCSSPrimitiveValueConstructor(ExecState* exec, const Identifier&, const PropertySlot& slot)
{
    return static_cast<JSCSSPrimitiveValue*>(asObject(slot.slotBase()))->getConstructor(exec);
}
JSValue JSCSSPrimitiveValue::getConstructor(ExecState* exec)
{
    return getDOMConstructor<JSCSSPrimitiveValueConstructor>(exec);
}

JSValue JSC_HOST_CALL jsCSSPrimitiveValuePrototypeFunctionSetFloatValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCSSPrimitiveValue::s_info))
        return throwError(exec, TypeError);
    JSCSSPrimitiveValue* castedThisObj = static_cast<JSCSSPrimitiveValue*>(asObject(thisValue));
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    unsigned short unitType = args.at(0).toInt32(exec);
    float floatValue = args.at(1).toFloat(exec);

    imp->setFloatValue(unitType, floatValue, ec);
    setDOMException(exec, ec);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsCSSPrimitiveValuePrototypeFunctionGetFloatValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCSSPrimitiveValue::s_info))
        return throwError(exec, TypeError);
    JSCSSPrimitiveValue* castedThisObj = static_cast<JSCSSPrimitiveValue*>(asObject(thisValue));
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    unsigned short unitType = args.at(0).toInt32(exec);


    JSC::JSValue result = jsNumber(exec, imp->getFloatValue(unitType, ec));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsCSSPrimitiveValuePrototypeFunctionSetStringValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCSSPrimitiveValue::s_info))
        return throwError(exec, TypeError);
    JSCSSPrimitiveValue* castedThisObj = static_cast<JSCSSPrimitiveValue*>(asObject(thisValue));
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(castedThisObj->impl());
    ExceptionCode ec = 0;
    unsigned short stringType = args.at(0).toInt32(exec);
    const UString& stringValue = args.at(1).toString(exec);

    imp->setStringValue(stringType, stringValue, ec);
    setDOMException(exec, ec);
    return jsUndefined();
}

JSValue JSC_HOST_CALL jsCSSPrimitiveValuePrototypeFunctionGetStringValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCSSPrimitiveValue::s_info))
        return throwError(exec, TypeError);
    JSCSSPrimitiveValue* castedThisObj = static_cast<JSCSSPrimitiveValue*>(asObject(thisValue));
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(castedThisObj->impl());
    ExceptionCode ec = 0;


    JSC::JSValue result = jsString(exec, imp->getStringValue(ec));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsCSSPrimitiveValuePrototypeFunctionGetCounterValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCSSPrimitiveValue::s_info))
        return throwError(exec, TypeError);
    JSCSSPrimitiveValue* castedThisObj = static_cast<JSCSSPrimitiveValue*>(asObject(thisValue));
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(castedThisObj->impl());
    ExceptionCode ec = 0;


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->getCounterValue(ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsCSSPrimitiveValuePrototypeFunctionGetRectValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCSSPrimitiveValue::s_info))
        return throwError(exec, TypeError);
    JSCSSPrimitiveValue* castedThisObj = static_cast<JSCSSPrimitiveValue*>(asObject(thisValue));
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(castedThisObj->impl());
    ExceptionCode ec = 0;


    JSC::JSValue result = toJS(exec, WTF::getPtr(imp->getRectValue(ec)));
    setDOMException(exec, ec);
    return result;
}

JSValue JSC_HOST_CALL jsCSSPrimitiveValuePrototypeFunctionGetRGBColorValue(ExecState* exec, JSObject*, JSValue thisValue, const ArgList& args)
{
    UNUSED_PARAM(args);
    if (!thisValue.isObject(&JSCSSPrimitiveValue::s_info))
        return throwError(exec, TypeError);
    JSCSSPrimitiveValue* castedThisObj = static_cast<JSCSSPrimitiveValue*>(asObject(thisValue));
    CSSPrimitiveValue* imp = static_cast<CSSPrimitiveValue*>(castedThisObj->impl());
    ExceptionCode ec = 0;


    JSC::JSValue result = getJSRGBColor(exec, imp->getRGBColorValue(ec));
    setDOMException(exec, ec);
    return result;
}

// Constant getters

JSValue jsCSSPrimitiveValueCSS_UNKNOWN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(0));
}

JSValue jsCSSPrimitiveValueCSS_NUMBER(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(1));
}

JSValue jsCSSPrimitiveValueCSS_PERCENTAGE(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(2));
}

JSValue jsCSSPrimitiveValueCSS_EMS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(3));
}

JSValue jsCSSPrimitiveValueCSS_EXS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(4));
}

JSValue jsCSSPrimitiveValueCSS_PX(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(5));
}

JSValue jsCSSPrimitiveValueCSS_CM(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(6));
}

JSValue jsCSSPrimitiveValueCSS_MM(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(7));
}

JSValue jsCSSPrimitiveValueCSS_IN(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(8));
}

JSValue jsCSSPrimitiveValueCSS_PT(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(9));
}

JSValue jsCSSPrimitiveValueCSS_PC(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(10));
}

JSValue jsCSSPrimitiveValueCSS_DEG(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(11));
}

JSValue jsCSSPrimitiveValueCSS_RAD(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(12));
}

JSValue jsCSSPrimitiveValueCSS_GRAD(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(13));
}

JSValue jsCSSPrimitiveValueCSS_MS(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(14));
}

JSValue jsCSSPrimitiveValueCSS_S(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(15));
}

JSValue jsCSSPrimitiveValueCSS_HZ(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(16));
}

JSValue jsCSSPrimitiveValueCSS_KHZ(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(17));
}

JSValue jsCSSPrimitiveValueCSS_DIMENSION(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(18));
}

JSValue jsCSSPrimitiveValueCSS_STRING(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(19));
}

JSValue jsCSSPrimitiveValueCSS_URI(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(20));
}

JSValue jsCSSPrimitiveValueCSS_IDENT(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(21));
}

JSValue jsCSSPrimitiveValueCSS_ATTR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(22));
}

JSValue jsCSSPrimitiveValueCSS_COUNTER(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(23));
}

JSValue jsCSSPrimitiveValueCSS_RECT(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(24));
}

JSValue jsCSSPrimitiveValueCSS_RGBCOLOR(ExecState* exec, const Identifier&, const PropertySlot&)
{
    return jsNumber(exec, static_cast<int>(25));
}


}