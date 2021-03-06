// Copyright 2015 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "apps/mozart/src/compositor/render/render_frame.h"

#include "apps/tracing/lib/trace/event.h"
#include "lib/ftl/logging.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkPicture.h"
#include "third_party/skia/include/core/SkRefCnt.h"

namespace compositor {

RenderFrame::RenderFrame(const Metadata& metadata, const SkIRect& viewport)
    : metadata_(metadata), viewport_(viewport) {
  FTL_DCHECK(!viewport_.isEmpty());
}

RenderFrame::RenderFrame(const Metadata& metadata,
                         const SkIRect& viewport,
                         const sk_sp<SkPicture>& picture,
                         ImageSet images)
    : metadata_(metadata),
      viewport_(viewport),
      picture_(picture),
      images_(std::move(images)) {
  FTL_DCHECK(!viewport_.isEmpty());
}

RenderFrame::~RenderFrame() {}

void RenderFrame::Draw(SkCanvas* canvas) const {
  FTL_DCHECK(canvas);
  TRACE_DURATION("gfx", "RenderFrame::Draw");

  // TODO: Consider using GrDrawContext instead of SkCanvas.
  canvas->clear(SK_ColorBLACK);
  if (picture_)
    canvas->drawPicture(picture_.get());
}

RenderFrame::Metadata::Metadata(const FrameInfo& frame_info,
                                ftl::TimePoint composition_time)
    : frame_info_(frame_info), composition_time_(composition_time) {}

RenderFrame::Metadata::~Metadata() {}

}  // namespace compositor
