// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8HTMLOptionElement.h"

#include "HTMLNames.h"
#include "bindings/core/v8/V8HTMLFormElement.h"
#include "bindings/v8/ExceptionState.h"
#include "bindings/v8/V8DOMConfiguration.h"
#include "bindings/v8/V8HiddenValue.h"
#include "bindings/v8/V8ObjectConstructor.h"
#include "core/dom/ContextFeatures.h"
#include "core/dom/Document.h"
#include "core/dom/custom/CustomElementCallbackDispatcher.h"
#include "core/frame/LocalDOMWindow.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "platform/TraceEvent.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace WebCore {

static void initializeScriptWrappableForInterface(HTMLOptionElement* object)
{
    if (ScriptWrappable::wrapperCanBeStoredInObject(object))
        ScriptWrappable::fromObject(object)->setTypeInfo(&V8HTMLOptionElement::wrapperTypeInfo);
    else
        ASSERT_NOT_REACHED();
}

} // namespace WebCore

void webCoreInitializeScriptWrappableForInterface(WebCore::HTMLOptionElement* object)
{
    WebCore::initializeScriptWrappableForInterface(object);
}

namespace WebCore {
const WrapperTypeInfo V8HTMLOptionElement::wrapperTypeInfo = { gin::kEmbedderBlink, V8HTMLOptionElement::domTemplate, V8HTMLOptionElement::derefObject, 0, V8HTMLOptionElement::toEventTarget, 0, V8HTMLOptionElement::installPerContextEnabledMethods, &V8HTMLElement::wrapperTypeInfo, WrapperTypeObjectPrototype, WillBeGarbageCollectedObject };

namespace HTMLOptionElementV8Internal {

template <typename T> void V8_USE(T) { }

static void disabledAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueBool(info, impl->fastHasAttribute(HTMLNames::disabledAttr));
}

static void disabledAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::disabledAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void disabledAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    TONATIVE_VOID(bool, cppValue, v8Value->BooleanValue());
    CustomElementCallbackDispatcher::CallbackDeliveryScope deliveryScope;
    impl->setBooleanAttribute(HTMLNames::disabledAttr, cppValue);
}

static void disabledAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    CustomElementCallbackDispatcher::CallbackDeliveryScope deliveryScope;
    HTMLOptionElementV8Internal::disabledAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void formAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueFast(info, WTF::getPtr(impl->form()), impl);
}

static void formAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::formAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void labelAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueString(info, impl->label(), info.GetIsolate());
}

static void labelAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::labelAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void labelAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    TOSTRING_VOID(V8StringResource<>, cppValue, v8Value);
    impl->setLabel(cppValue);
}

static void labelAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    HTMLOptionElementV8Internal::labelAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void defaultSelectedAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueBool(info, impl->fastHasAttribute(HTMLNames::selectedAttr));
}

static void defaultSelectedAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::defaultSelectedAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void defaultSelectedAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    TONATIVE_VOID(bool, cppValue, v8Value->BooleanValue());
    CustomElementCallbackDispatcher::CallbackDeliveryScope deliveryScope;
    impl->setBooleanAttribute(HTMLNames::selectedAttr, cppValue);
}

static void defaultSelectedAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    CustomElementCallbackDispatcher::CallbackDeliveryScope deliveryScope;
    HTMLOptionElementV8Internal::defaultSelectedAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void selectedAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueBool(info, impl->selected());
}

static void selectedAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::selectedAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void selectedAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    TONATIVE_VOID(bool, cppValue, v8Value->BooleanValue());
    impl->setSelected(cppValue);
}

static void selectedAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    HTMLOptionElementV8Internal::selectedAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void valueAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueString(info, impl->value(), info.GetIsolate());
}

static void valueAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::valueAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void valueAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    TOSTRING_VOID(V8StringResource<>, cppValue, v8Value);
    impl->setValue(cppValue);
}

static void valueAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    HTMLOptionElementV8Internal::valueAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void textAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueString(info, impl->text(), info.GetIsolate());
}

static void textAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::textAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void textAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    ExceptionState exceptionState(ExceptionState::SetterContext, "text", "HTMLOptionElement", holder, info.GetIsolate());
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    TOSTRING_VOID(V8StringResource<>, cppValue, v8Value);
    impl->setText(cppValue, exceptionState);
    exceptionState.throwIfNeeded();
}

static void textAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMSetter");
    HTMLOptionElementV8Internal::textAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

static void indexAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    HTMLOptionElement* impl = V8HTMLOptionElement::toNative(holder);
    v8SetReturnValueInt(info, impl->index());
}

static void indexAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("Blink", "DOMGetter");
    HTMLOptionElementV8Internal::indexAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("V8", "V8Execution");
}

} // namespace HTMLOptionElementV8Internal

static const V8DOMConfiguration::AttributeConfiguration V8HTMLOptionElementAttributes[] = {
    {"disabled", HTMLOptionElementV8Internal::disabledAttributeGetterCallback, HTMLOptionElementV8Internal::disabledAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"form", HTMLOptionElementV8Internal::formAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"label", HTMLOptionElementV8Internal::labelAttributeGetterCallback, HTMLOptionElementV8Internal::labelAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"defaultSelected", HTMLOptionElementV8Internal::defaultSelectedAttributeGetterCallback, HTMLOptionElementV8Internal::defaultSelectedAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"selected", HTMLOptionElementV8Internal::selectedAttributeGetterCallback, HTMLOptionElementV8Internal::selectedAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"value", HTMLOptionElementV8Internal::valueAttributeGetterCallback, HTMLOptionElementV8Internal::valueAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"text", HTMLOptionElementV8Internal::textAttributeGetterCallback, HTMLOptionElementV8Internal::textAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
    {"index", HTMLOptionElementV8Internal::indexAttributeGetterCallback, 0, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
};

const WrapperTypeInfo V8HTMLOptionElementConstructor::wrapperTypeInfo = { gin::kEmbedderBlink, V8HTMLOptionElementConstructor::domTemplate, V8HTMLOptionElement::derefObject, 0, V8HTMLOptionElement::toEventTarget, 0, V8HTMLOptionElement::installPerContextEnabledMethods, 0, WrapperTypeObjectPrototype, WillBeGarbageCollectedObject };

static void V8HTMLOptionElementConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    v8::Isolate* isolate = info.GetIsolate();
    if (!info.IsConstructCall()) {
        throwTypeError(ExceptionMessages::constructorNotCallableAsFunction("Option"), isolate);
        return;
    }

    if (ConstructorMode::current(isolate) == ConstructorMode::WrapExistingObject) {
        v8SetReturnValue(info, info.Holder());
        return;
    }

    Document* documentPtr = currentDOMWindow(isolate)->document();
    ASSERT(documentPtr);
    Document& document = *documentPtr;

    // Make sure the document is added to the DOM Node map. Otherwise, the HTMLOptionElement instance
    // may end up being the only node in the map and get garbage-collected prematurely.
    toV8(documentPtr, info.Holder(), isolate);

    ExceptionState exceptionState(ExceptionState::ConstructionContext, "HTMLOptionElement", info.Holder(), isolate);
    V8StringResource<> data;
    V8StringResource<> value;
    bool defaultSelected;
    bool selected;
    {
        v8::TryCatch block;
        V8RethrowTryCatchScope rethrow(block);
        TOSTRING_VOID_INTERNAL(data, argumentOrNull(info, 0));
        TOSTRING_VOID_INTERNAL(value, argumentOrNull(info, 1));
        TONATIVE_VOID_INTERNAL(defaultSelected, info[2]->BooleanValue());
        TONATIVE_VOID_INTERNAL(selected, info[3]->BooleanValue());
    }
    RefPtrWillBeRawPtr<HTMLOptionElement> impl = HTMLOptionElement::createForJSConstructor(document, data, value, defaultSelected, selected, exceptionState);
    if (exceptionState.throwIfNeeded())
        return;

    v8::Handle<v8::Object> wrapper = info.Holder();
    V8DOMWrapper::associateObjectWithWrapper<V8HTMLOptionElement>(impl.release(), &V8HTMLOptionElementConstructor::wrapperTypeInfo, wrapper, isolate, WrapperConfiguration::Dependent);
    v8SetReturnValue(info, wrapper);
}

v8::Handle<v8::FunctionTemplate> V8HTMLOptionElementConstructor::domTemplate(v8::Isolate* isolate)
{
    static int domTemplateKey; // This address is used for a key to look up the dom template.
    V8PerIsolateData* data = V8PerIsolateData::from(isolate);
    v8::Local<v8::FunctionTemplate> result = data->existingDOMTemplate(&domTemplateKey);
    if (!result.IsEmpty())
        return result;

    TRACE_EVENT_SCOPED_SAMPLING_STATE("Blink", "BuildDOMTemplate");
    result = v8::FunctionTemplate::New(isolate, V8HTMLOptionElementConstructorCallback);
    v8::Local<v8::ObjectTemplate> instanceTemplate = result->InstanceTemplate();
    instanceTemplate->SetInternalFieldCount(V8HTMLOptionElement::internalFieldCount);
    result->SetClassName(v8AtomicString(isolate, "HTMLOptionElement"));
    result->Inherit(V8HTMLOptionElement::domTemplate(isolate));
    data->setDOMTemplate(&domTemplateKey, result);
    return result;
}

static void configureV8HTMLOptionElementTemplate(v8::Handle<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::installDOMClassTemplate(functionTemplate, "HTMLOptionElement", V8HTMLElement::domTemplate(isolate), V8HTMLOptionElement::internalFieldCount,
        V8HTMLOptionElementAttributes, WTF_ARRAY_LENGTH(V8HTMLOptionElementAttributes),
        0, 0,
        0, 0,
        isolate);
    v8::Local<v8::ObjectTemplate> instanceTemplate ALLOW_UNUSED = functionTemplate->InstanceTemplate();
    v8::Local<v8::ObjectTemplate> prototypeTemplate ALLOW_UNUSED = functionTemplate->PrototypeTemplate();

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Handle<v8::FunctionTemplate> V8HTMLOptionElement::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), configureV8HTMLOptionElementTemplate);
}

bool V8HTMLOptionElement::hasInstance(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Handle<v8::Object> V8HTMLOptionElement::findInstanceInPrototypeChain(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

HTMLOptionElement* V8HTMLOptionElement::toNativeWithTypeCheck(v8::Isolate* isolate, v8::Handle<v8::Value> value)
{
    return hasInstance(value, isolate) ? fromInternalPointer(v8::Handle<v8::Object>::Cast(value)->GetAlignedPointerFromInternalField(v8DOMWrapperObjectIndex)) : 0;
}

EventTarget* V8HTMLOptionElement::toEventTarget(v8::Handle<v8::Object> object)
{
    return toNative(object);
}

v8::Handle<v8::Object> wrap(HTMLOptionElement* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8HTMLOptionElement>(impl, isolate));
    return V8HTMLOptionElement::createWrapper(impl, creationContext, isolate);
}

v8::Handle<v8::Object> V8HTMLOptionElement::createWrapper(PassRefPtrWillBeRawPtr<HTMLOptionElement> impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl);
    ASSERT(!DOMDataStore::containsWrapper<V8HTMLOptionElement>(impl.get(), isolate));
    if (ScriptWrappable::wrapperCanBeStoredInObject(impl.get())) {
        const WrapperTypeInfo* actualInfo = ScriptWrappable::fromObject(impl.get())->typeInfo();
        // Might be a XXXConstructor::wrapperTypeInfo instead of an XXX::wrapperTypeInfo. These will both have
        // the same object de-ref functions, though, so use that as the basis of the check.
        RELEASE_ASSERT_WITH_SECURITY_IMPLICATION(actualInfo->derefObjectFunction == wrapperTypeInfo.derefObjectFunction);
    }

    v8::Handle<v8::Object> wrapper = V8DOMWrapper::createWrapper(creationContext, &wrapperTypeInfo, toInternalPointer(impl.get()), isolate);
    if (UNLIKELY(wrapper.IsEmpty()))
        return wrapper;

    installPerContextEnabledProperties(wrapper, impl.get(), isolate);
    V8DOMWrapper::associateObjectWithWrapper<V8HTMLOptionElement>(impl, &wrapperTypeInfo, wrapper, isolate, WrapperConfiguration::Dependent);
    return wrapper;
}

void V8HTMLOptionElement::derefObject(void* object)
{
#if !ENABLE(OILPAN)
    fromInternalPointer(object)->deref();
#endif // !ENABLE(OILPAN)
}

template<>
v8::Handle<v8::Value> toV8NoInline(HTMLOptionElement* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    return toV8(impl, creationContext, isolate);
}

} // namespace WebCore
