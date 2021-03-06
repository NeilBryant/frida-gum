/*
 * Copyright (C) 2008 Ole André Vadla Ravnås <ole.andre.ravnas@tillitech.com>
 *
 * Licence: wxWindows Library Licence, Version 3.1
 */

#include "fakebacktracer.h"
#include <string.h>

static void gum_fake_backtracer_iface_init (gpointer g_iface,
    gpointer iface_data);
static void gum_fake_backtracer_generate (GumBacktracer * backtracer,
    const GumCpuContext * cpu_context,
    GumReturnAddressArray * return_addresses);

G_DEFINE_TYPE_EXTENDED (GumFakeBacktracer,
                        gum_fake_backtracer,
                        G_TYPE_OBJECT,
                        0,
                        G_IMPLEMENT_INTERFACE (GUM_TYPE_BACKTRACER,
                                               gum_fake_backtracer_iface_init));

static void
gum_fake_backtracer_class_init (GumFakeBacktracerClass * klass)
{
}

static void
gum_fake_backtracer_iface_init (gpointer g_iface,
                                gpointer iface_data)
{
  GumBacktracerIface * iface = (GumBacktracerIface *) g_iface;

  iface->generate = gum_fake_backtracer_generate;
}

static void
gum_fake_backtracer_init (GumFakeBacktracer * self)
{
}

GumBacktracer *
gum_fake_backtracer_new (const GumReturnAddress * ret_addrs,
                         guint num_ret_addrs)
{
  GumFakeBacktracer * backtracer;

  backtracer = g_object_new (GUM_TYPE_FAKE_BACKTRACER, NULL);
  backtracer->ret_addrs = ret_addrs;
  backtracer->num_ret_addrs = num_ret_addrs;

  return GUM_BACKTRACER (backtracer);
}

static void
gum_fake_backtracer_generate (GumBacktracer * backtracer,
                              const GumCpuContext * cpu_context,
                              GumReturnAddressArray * return_addresses)
{
  GumFakeBacktracer * self = GUM_FAKE_BACKTRACER (backtracer);

  memcpy (return_addresses->items, self->ret_addrs, self->num_ret_addrs *
      sizeof (GumReturnAddress));
  return_addresses->len = self->num_ret_addrs;
}
